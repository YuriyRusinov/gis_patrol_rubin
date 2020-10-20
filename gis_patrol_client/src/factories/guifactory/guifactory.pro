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
INCLUDEPATH *= ../pgui ../pgui/ui
DEPENDPATH *= ../pgui ../pgui/ui
#
# core
#
INCLUDEPATH *= ../../corelibs
DEPENDPATH *= ../../corelibs

QT += core widgets location

LIBS *= -L$${DESTDIR} -lgis_patrol_utils -ldataaccess -lpatrolCommunications -lpgui -lcorelibs
include( guifactory.pri )
