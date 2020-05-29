TEMPLATE = lib

include(../../gis_patrol_client.conf)

TARGET = corelibs
DESTDIR = ../../build

CONFIG += qt
#
# utils
#
INCLUDEPATH *= ../gis_patrolutils
DEPENDPATH *= ../gis_patrolutils
#
# databases
#
INCLUDEPATH *= ../dataaccess
DEPENDPATH *= ../dataaccess

QT += core widgets

CONFIG += link_pkgconfig
PKGCONFIG += libpq gsl

LIBS *= -L$${DESTDIR} -lgis_patrol_utils -ldataaccess

include (corelibs.pri)
