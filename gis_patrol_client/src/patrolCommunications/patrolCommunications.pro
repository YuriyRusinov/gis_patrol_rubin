TEMPLATE = lib
include (../../gis_patrol_client.conf)
TARGET = patrolCommunications

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
#
# corelibs
#
INCLUDEPATH *= ../corelibs
DEPENDPATH *= ../corelibs

QT += core widgets xml 

CONFIG += link_pkgconfig
PKGCONFIG += libpq gsl

LIBS *= -L$${DESTDIR} -lgis_patrol_utils -ldataaccess -lcorelibs

include(patrolCommunications.pri)
