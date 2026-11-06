#pragma once
#include "core/modules.h"
#include <QMainWindow>
class QMdiArea;
class QTreeWidget;
class QTableWidget;
namespace filmstation {
class MainWindow : public QMainWindow {
public:
 explicit MainWindow(const ModuleRegistry& registry);
 void openView(const QString& moduleId, const QString& viewId);
private:
 void inspect(const QString& moduleId, const QString& viewId);
 const ModuleRegistry& registry_;
 QMdiArea* workspace_;
 QTreeWidget* project_;
 QTableWidget* properties_;
};
}
