TEMPLATE = lib

include(../../../gis_patrol_client.conf)

TARGET = pgui
DESTDIR = ../../../build
CONFIG += qt

QT += core widgets

LIBS *= -L$${DESTDIR} -lgis_patrol_utils -lpatrolCommunications

include(pgui.pri)
