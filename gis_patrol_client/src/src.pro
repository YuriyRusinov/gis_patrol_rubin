TEMPLATE = subdirs

RESOURCES = patrol_icons/patrol.qrc
QMAKE_RPATHDIR += $${DESTDIR}

SUBDIRS += \
          gis_patrolutils \
          dataaccess \
          corelibs
