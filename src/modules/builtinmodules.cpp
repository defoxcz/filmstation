#include "core/modules.h"
#include <QCoreApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <stdexcept>
namespace filmstation {
namespace {
QString text(const char* s) { return QCoreApplication::translate("Modules", s); }
class PlanningModule final : public IModule {
 QString id_, title_; QList<ViewDefinition> views_;
public:
 PlanningModule(QString id, QString title, QList<ViewDefinition> views): id_(id),title_(title),views_(views) {}
 QString id() const override { return id_; }
 QString title() const override { return title_; }
 QList<ViewDefinition> views() const override { return views_; }
 QWidget* createView(const QString& id, QWidget* parent) const override {
  for(const auto& view: views_) if(view.id==id) {
   auto* widget=new QWidget(parent);
   auto* layout=new QVBoxLayout(widget);
   auto* heading=new QLabel(view.title,widget);
   QFont font=heading->font(); font.setPointSize(20); heading->setFont(font);
   layout->addWidget(heading);
   auto* description=new QLabel(text("This module is registered. Its production editor is not implemented yet."),widget);
   description->setWordWrap(true); layout->addWidget(description); layout->addStretch();
   return widget;
  }
  return nullptr;
 }
};
}
void registerBuiltInModules(ModuleRegistry& registry) {
 auto add=[&](const char* id,const char* title,QList<ViewDefinition> views) {
  QString error;
  if(!registry.add(std::make_unique<PlanningModule>(QString::fromLatin1(id),text(title),views),&error))
   throw std::runtime_error(error.toStdString());
 };
 add("scripts","Scripts",{{"literary",text("Literary script")},{"technical",text("Technical script")}});
 add("cast","Cast & Characters",{{"actors",text("Actors")},{"characters",text("Characters")}});
 add("crew","Crew",{{"directory",text("Crew directory")}});
 add("locations","Locations",{{"directory",text("Location directory")}});
 add("schedule","Scheduling",{{"calendar",text("Production calendar")},{"stripboard",text("Shooting schedule")}});
 add("budget","Budgeting",{{"budget",text("Production budget")}});
 add("resources","Production Resources",{{"resources",text("Equipment, props & costumes")}});
 add("reports","Reports",{{"callsheets",text("Call sheets")},{"overview",text("Production overview")}});
}
}
