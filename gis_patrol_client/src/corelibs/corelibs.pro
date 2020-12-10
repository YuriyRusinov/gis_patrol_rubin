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
#
# gui
#
INCLUDEPATH *= ../factories/pgui
DEPENDPATH *= ../factories/pgui
#
# guifactory
#
INCLUDEPATH *= ../factories/guifactory
DEPENDPATH *= ../factories/guifactory
#
# main entities
#
INCLUDEPATH *= ../patrolCommunications
DEPENDPATH *= ../patrolCommunications

QT += core widgets

CONFIG += link_pkgconfig
PKGCONFIG += libpq gsl

LIBS *= -L$${DESTDIR} -lgis_patrol_utils -ldataaccess -lpgui -lpatrolCommunications

include (corelibs.pri)

TRANSLATIONS += ../../transl/patrol_ru.ts
