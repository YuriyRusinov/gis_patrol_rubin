TEMPLATE = lib

include(../../../gis_patrol_client.conf)

TARGET = pgui
DESTDIR = ../../../build
CONFIG += qt

INCLUDEPATH *= ../../patrolCommunications
DEPENDPATH *= ../../patrolCommunications

INCLUDEPATH *= ../../gis_patrolutils

QT += core widgets svg

LIBS *= -L$${DESTDIR} -lgis_patrol_utils -lpatrolCommunications

include(pgui.pri)
