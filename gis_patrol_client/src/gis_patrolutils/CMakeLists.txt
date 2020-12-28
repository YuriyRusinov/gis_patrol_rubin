cmake_minimum_required(VERSION 3.7)

project(gis_patrolutils VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(HEADERS
		defines.h
		cast.h
		deleteptr.h
		configUtils.h
		configEndians.h
		strutils.h
		gis_patrol_minixml.h
		gis_patrol_getsymbol.h
		gis_patrol_port.h
)

set(SOURCES
		gis_patrol_minixml.cpp
		strutils.cpp
		gis_patrol_getsymbol.cpp
		cast.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME})# ${SOURCES} ${HEADERS})


