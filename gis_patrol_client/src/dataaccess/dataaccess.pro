# dataaccess

TEMPLATE = lib
TARGET = dataaccess

DESTDIR = ../../build
include(../../gis_patrol_client.conf)
#utils support
INCLUDEPATH *= ../gis_patrolutils
DEPENDPATH *= ../gis_patrolutils
LIBS *= -L$$DESTDIR -lgis_patrol_utils

INCLUDEPATH += ./

CONFIG += qt

CONFIG += warn_on dll
CONFIG += link_pkgconfig

DEFINES += __USE_DLL_DATAACCESS
#DEFINES -= UNICODE

# libpq support
PKGCONFIG += libpq

#win32 {
#!win32-g++:LIBS *= libpqdll.lib
#win32-g++:LIBS += $${PSQL_HOME}/lib/libpq.dll.a
#}
#unix: LIBS += -lpq

include (dataaccess.pri)

# install targets
# headers
headers.path = $$GIS_PATROL_INCLUDE_DIR

# import lib
win32 {
	implib.path = $$GIS_PATROL_LIB_DIR
	implib.files = $$sprintf("%1/%2.lib", $$DESTDIR, $$TARGET)

	# lib
	target.path = $$GIS_PATROL_BIN_DIR
	debug {
		target.files = \
			$$sprintf("%1/%2.dll", $$DESTDIR, $$TARGET) \
			$$sprintf("%1/%2.pdb", $$DESTDIR, $$TARGET) \
			$$sprintf("%1/%2.ilk", $$DESTDIR, $$TARGET) \
			$$sprintf("%1/%2.exp", $$DESTDIR, $$TARGET)
	}
	release {
		target.files = \
			$$sprintf("%1/%2.dll", $$DESTDIR, $$TARGET)
	}
}
unix {
	target.path = $$GIS_PATROL_LIB_DIR 
}


INSTALLS += target headers
win32{
	INSTALLS += implib
}
