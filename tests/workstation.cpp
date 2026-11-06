#include "ui/mainwindow.h"
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QTableWidget>
#include <QtTest>
class WorkstationTest: public QObject {
 Q_OBJECT
private slots:
 void registryAndWorkspace() {
  filmstation::ModuleRegistry registry;
  QString error;
  QVERIFY(!registry.add(nullptr,&error)); QVERIFY(!error.isEmpty());
  filmstation::registerBuiltInModules(registry);
  QCOMPARE(registry.modules().size(),8);
  QVERIFY(registry.find("budget"));
  bool duplicateRejected=false;
  try { filmstation::registerBuiltInModules(registry); } catch(const std::exception&) { duplicateRejected=true; }
  QVERIFY(duplicateRejected); QCOMPARE(registry.modules().size(),8);
  filmstation::MainWindow window(registry); window.show();
  auto* area=window.findChild<QMdiArea*>("workspace"); QVERIFY(area);
  window.openView("scripts","literary"); window.openView("budget","budget");
  QCOMPARE(area->subWindowList().size(),2);
  window.openView("scripts","literary"); QCOMPARE(area->subWindowList().size(),2);
  QCOMPARE(area->activeSubWindow()->property("moduleId").toString(),QString("scripts"));
  auto* grid=window.findChild<QTableWidget*>("propertyGrid"); QVERIFY(grid);
  QCOMPARE(grid->item(0,1)->text(),QString("Scripts"));
  window.openView("scripts","missing"); QCOMPARE(area->subWindowList().size(),2);
  area->closeActiveSubWindow(); QCoreApplication::sendPostedEvents(nullptr,QEvent::DeferredDelete);
  QCOMPARE(area->subWindowList().size(),1);
  window.openView("scripts","literary"); QCOMPARE(area->subWindowList().size(),2);
 }
};
QTEST_MAIN(WorkstationTest)
#include "workstation.moc"
