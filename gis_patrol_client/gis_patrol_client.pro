TEMPLATE = subdirs

include(./gis_patrol_client.conf)

SUBDIRS += \
            src \
            app

#transl
transl.files = ./transl/*.qm
transl.path = $$GIS_PATROL_TRANSL_DIR

INSTALLS += transl
TRANSLATIONS = ./transl/gis_patrol_ru.ts 
