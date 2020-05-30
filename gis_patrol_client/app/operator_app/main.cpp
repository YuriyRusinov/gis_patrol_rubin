#include <QApplication>
#include "patrolmainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    PatrolMainWindow* pmw = new PatrolMainWindow;

    pmw->show();
    int ret = app.exec();
    delete pmw;//->deleteLater();
    return ret;
}
