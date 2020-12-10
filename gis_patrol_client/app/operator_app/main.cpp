#include <QApplication>
#include <patrolsingleton.h>
#include "patrolmainwindow.h"

int main(int argc, char* argv[]) {
    Q_INIT_RESOURCE( gis_patrol );
    QApplication app(argc, argv);
    PatrolSingleton* _patrolS = PatrolSingleton::getPatrolS();
    _patrolS->installTranslator();
    PatrolMainWindow* pmw = new PatrolMainWindow;

    pmw->show();
    int ret = app.exec();
    delete pmw;//->deleteLater();
    return ret;
}
