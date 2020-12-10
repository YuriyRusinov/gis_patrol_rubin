TEMPLATE = subdirs
DESTDIR = ./build
include(./gis_patrol_client.conf)

QMAKE_RPATHDIR += $${DESTDIR}
message("runtime library path is $${QMAKE_RPATHDIR}")

SUBDIRS += \
            src \
            app


#transl
transl.files = ./transl/*.qm
transl.path = $$GIS_PATROL_TRANSL_DIR

INSTALLS += transl
TRANSLATIONS = ./transl/patrol_ru.ts 

RESOURCES += gis_patrol.qrc
