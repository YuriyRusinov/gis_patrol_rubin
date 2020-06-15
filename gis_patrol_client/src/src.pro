TEMPLATE = subdirs

RESOURCES = patrol_icons/patrol.qrc
QMAKE_RPATHDIR += $${DESTDIR}
CONFIG += c++11

SUBDIRS += \
          gis_patrolutils \
          dataaccess \
          patrolCommunications \
          factories \
          corelibs
