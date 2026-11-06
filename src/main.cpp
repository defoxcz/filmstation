#include "ui/mainwindow.h"
#include <QApplication>
int main(int argc,char** argv) {
 QApplication app(argc,argv);
 QCoreApplication::setApplicationName("FilmStation");
 QCoreApplication::setApplicationVersion("0.1.0");
 filmstation::ModuleRegistry modules;
 filmstation::registerBuiltInModules(modules);
 filmstation::MainWindow window(modules);
 window.show();
 return app.exec();
}
