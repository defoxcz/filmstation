#include "core/modules.h"
#include <QSet>
namespace filmstation {
bool ModuleRegistry::add(std::unique_ptr<IModule> module, QString* error) {
 auto fail = [&](const QString& message) { if(error) *error=message; return false; };
 if (!module || module->id().trimmed().isEmpty()) return fail(QStringLiteral("Missing module ID"));
 if (find(module->id())) return fail(QStringLiteral("Duplicate module ID"));
 QSet<QString> ids;
 for (const auto& view : module->views()) {
  if(view.id.trimmed().isEmpty() || ids.contains(view.id)) return fail(QStringLiteral("Invalid or duplicate view ID"));
  ids.insert(view.id);
 }
 modules_.push_back(std::move(module));
 if(error) error->clear();
 return true;
}
const IModule* ModuleRegistry::find(const QString& id) const {
 for(const auto& module: modules_) if(module->id()==id) return module.get();
 return nullptr;
}
QList<const IModule*> ModuleRegistry::modules() const {
 QList<const IModule*> result;
 for(const auto& module: modules_) result.append(module.get());
 return result;
}
}
