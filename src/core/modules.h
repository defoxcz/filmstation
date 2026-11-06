#pragma once
#include <QString>
#include <QList>
#include <QWidget>
#include <memory>
#include <vector>
namespace filmstation {
struct ViewDefinition { QString id; QString title; };
// Stable identifiers belong to modules; UI labels are translated independently.
class IModule {
public:
 virtual ~IModule() = default;
 virtual QString id() const = 0;
 virtual QString title() const = 0;
 virtual QList<ViewDefinition> views() const = 0;
 virtual QWidget* createView(const QString& viewId, QWidget* parent) const = 0;
};
class ModuleRegistry {
public:
 bool add(std::unique_ptr<IModule> module, QString* error = nullptr);
 const IModule* find(const QString& id) const;
 QList<const IModule*> modules() const;
private:
 std::vector<std::unique_ptr<IModule>> modules_;
};
void registerBuiltInModules(ModuleRegistry& registry);
}
