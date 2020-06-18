TEMPLATE = lib

include(../../../gis_patrol_client.conf)

TARGET = guifactory
DESTDIR = ../../../build

CONFIG += qt
#
# utils
#
INCLUDEPATH *= ../../gis_patrolutils
DEPENDPATH *= ../../gis_patrolutils
#
# databases
#
INCLUDEPATH *= ../../dataaccess
DEPENDPATH *= ../../dataaccess
#
# patrolCommunications
#
INCLUDEPATH *= ../../patrolCommunications
DEPENDPATH *= ../../patrolCommunications
#
# gui
#
INCLUDEPATH *= ../pgui
DEPENDPATH *= ../pgui
#
# core
#
INCLUDEPATH *= ../../corelibs
DEPENDPATH *= ../../corelibs

QT += core widgets

LIBS *= -L$${DESTDIR} -lgis_patrol_utils -ldataaccess -lpatrolCommunications -lpgui -lcorelibs
include( guifactory.pri )
