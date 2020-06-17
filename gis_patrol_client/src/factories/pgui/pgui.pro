TEMPLATE = lib

include(../../../gis_patrol_client.conf)

TARGET = pgui
DESTDIR = ../../../build
CONFIG += qt

INCLUDEPATH *= ../../patrolCommunications
DEPENDPATH *= ../../patrolCommunications

QT += core widgets

LIBS *= -L$${DESTDIR} -lgis_patrol_utils -lpatrolCommunications

include(pgui.pri)
