#include "../include/mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    QSurfaceFormat fmt;
    fmt.setRenderableType(QSurfaceFormat::OpenGL);
    fmt.setVersion(2, 1);
    fmt.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    fmt.setSamples(4);
    QSurfaceFormat::setDefaultFormat(fmt);

    MainWindow w;
    w.show();
    
    return a.exec();
}