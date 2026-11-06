#include "ui/mainwindow.h"
#include <QDockWidget>
#include <QHeaderView>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QTableWidget>
#include <QTreeWidget>
namespace filmstation {
MainWindow::MainWindow(const ModuleRegistry& registry):registry_(registry) {
 setWindowTitle(tr("FilmStation — The Film Production Workstation")); resize(1440,900);
 workspace_=new QMdiArea(this); workspace_->setObjectName("workspace"); setCentralWidget(workspace_);
 auto* projectDock=new QDockWidget(tr("Project"),this); projectDock->setObjectName("projectDock");
 project_=new QTreeWidget(projectDock); project_->setObjectName("projectTree"); project_->setHeaderHidden(true);
 auto* root=new QTreeWidgetItem(project_,{tr("Production workspace")});
 for(const auto* module:registry_.modules()) {
  auto* item=new QTreeWidgetItem(root,{module->title()}); item->setData(0,Qt::UserRole,module->id());
  for(const auto& view:module->views()) {
   auto* child=new QTreeWidgetItem(item,{view.title}); child->setData(0,Qt::UserRole,module->id()); child->setData(0,Qt::UserRole+1,view.id);
  }
 }
 root->setExpanded(true); projectDock->setWidget(project_); addDockWidget(Qt::LeftDockWidgetArea,projectDock);
 auto* propertyDock=new QDockWidget(tr("Properties"),this); propertyDock->setObjectName("propertyDock");
 properties_=new QTableWidget(0,2,propertyDock); properties_->setObjectName("propertyGrid");
 properties_->setHorizontalHeaderLabels({tr("Property"),tr("Value")}); properties_->horizontalHeader()->setStretchLastSection(true);
 properties_->verticalHeader()->hide(); properties_->setEditTriggers(QAbstractItemView::NoEditTriggers);
 propertyDock->setWidget(properties_); addDockWidget(Qt::RightDockWidgetArea,propertyDock);
 resizeDocks({projectDock,propertyDock},{250,300},Qt::Horizontal);
 connect(project_,&QTreeWidget::itemDoubleClicked,this,[this](QTreeWidgetItem* item,int){openView(item->data(0,Qt::UserRole).toString(),item->data(0,Qt::UserRole+1).toString());});
 connect(project_,&QTreeWidget::currentItemChanged,this,[this](QTreeWidgetItem* item){ if(item) inspect(item->data(0,Qt::UserRole).toString(),item->data(0,Qt::UserRole+1).toString()); });
 connect(workspace_,&QMdiArea::subWindowActivated,this,[this](QMdiSubWindow* window){if(window) inspect(window->property("moduleId").toString(),window->property("viewId").toString()); else properties_->setRowCount(0);});
 auto* file=menuBar()->addMenu(tr("&File")); file->addAction(tr("Quit"),QKeySequence::Quit,this,&QWidget::close);
 auto* viewMenu=menuBar()->addMenu(tr("&View")); viewMenu->addAction(projectDock->toggleViewAction()); viewMenu->addAction(propertyDock->toggleViewAction());
 auto* windows=menuBar()->addMenu(tr("&Window"));
 windows->addAction(tr("Tile"),workspace_,&QMdiArea::tileSubWindows);
 windows->addAction(tr("Cascade"),workspace_,&QMdiArea::cascadeSubWindows);
 windows->addAction(tr("Close active view"),workspace_,&QMdiArea::closeActiveSubWindow);
 statusBar()->showMessage(tr("Foundation preview — double-click a view in the project tree"));
}
void MainWindow::openView(const QString& moduleId,const QString& viewId) {
 const auto* module=registry_.find(moduleId); if(!module) return;
 for(auto* window:workspace_->subWindowList()) {
  if(window->property("moduleId")==moduleId && window->property("viewId")==viewId) { window->showNormal(); workspace_->setActiveSubWindow(window); return; }
 }
 QString title;
 for(const auto& view:module->views()) if(view.id==viewId) title=view.title;
 if(title.isEmpty()) return;
 auto* widget=module->createView(viewId,workspace_); if(!widget) return;
 auto* window=workspace_->addSubWindow(widget); window->setAttribute(Qt::WA_DeleteOnClose);
 window->setProperty("moduleId",moduleId); window->setProperty("viewId",viewId);
 window->setWindowTitle(module->title()+" — "+title); window->resize(700,480); window->show();
 workspace_->setActiveSubWindow(window); inspect(moduleId,viewId);
}
void MainWindow::inspect(const QString& moduleId,const QString& viewId) {
 properties_->setRowCount(0);
 const auto* module=registry_.find(moduleId); if(!module) return;
 auto row=[&](const QString& key,const QString& value){int r=properties_->rowCount(); properties_->insertRow(r); properties_->setItem(r,0,new QTableWidgetItem(key)); properties_->setItem(r,1,new QTableWidgetItem(value));};
 row(tr("Module"),module->title());
 for(const auto& view:module->views()) if(view.id==viewId) row(tr("View"),view.title);
 row(tr("Status"),tr("Editor planned"));
}
}
