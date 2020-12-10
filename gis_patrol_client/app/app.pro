TEMPLATE = subdirs

DESTDIR = ../build
QMAKE_RPATHDIR += $${DESTDIR}
message("app runtime library path is $${QMAKE_RPATHDIR}")

include(../gis_patrol_client.conf)

SUBDIRS += \
           operator_app

TRANSLATIONS += ../transl/patrol_ru.ts
