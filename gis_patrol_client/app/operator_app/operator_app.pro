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

QT += core widgets

LIBS *= -L$${DESTDIR} -lgis_patrol_utils -ldataaccess -lcorelibs

HEADERS += patrolmainwindow.h

FORMS += patrol_main_window.ui

SOURCES += \
           patrolmainwindow.cpp \
           main.cpp

RESOURCES = ../../src/patrol_icons/patrol.qrc