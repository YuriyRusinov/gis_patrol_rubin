TEMPLATE = app

include(../../gis_patrol_client.conf)

TARGET = operator_app
DESTDIR = ../../build

CONFIG += qt
#
# utils
#
INCLUDEPATH *= ../../src/gis_patrolutils
DEPENDPATH *= ../../src/gis_patrolutils
#
# databases
#
INCLUDEPATH *= ../../src/dataaccess
DEPENDPATH *= ../../src/dataaccess
#
# corelibs
#
INCLUDEPATH *= ../../src/corelibs
DEPENDPATH *= ../../src/corelibs
#
# patrolCommunications
#
INCLUDEPATH *= ../../src/patrolCommunications
DEPENDPATH *= ../../src/patrolCommunications
#
# guifactories
#
INCLUDEPATH *= ../../src/factories/guifactory
DEPENDPATH *= ../../src/factories/guifactory

QT += core widgets

LIBS *= -L$${DESTDIR} -lgis_patrol_utils
LIBS *= -L$${DESTDIR} -ldataaccess
LIBS *= -L$${DESTDIR} -lcorelibs
LIBS *= -L$${DESTDIR} -lpatrolCommunications
LIBS *= -L$${DESTDIR} -lguifactory

QMAKE_REL_RPATH_BASE = $$PWD
QMAKE_RPATHDIR += $${DESTDIR}
message("operator app runtime library path is $${QMAKE_RPATHDIR}")

HEADERS += patrolmainwindow.h

FORMS += patrol_main_window.ui

SOURCES += \
           patrolmainwindow.cpp \
           main.cpp

RESOURCES = ../../src/patrol_icons/patrol.qrc
