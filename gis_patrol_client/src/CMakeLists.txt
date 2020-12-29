cmake_minimum_required(VERSION 3.7)

project(gis_patrol_src VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(gis_patrolutils)
add_subdirectory(dataaccess)
add_subdirectory(patrolCommunications)
add_subdirectory(factories)
add_subdirectory(corelibs)

#target_link_libraries(gis_patrolutils dataaccess patrolCommunications factories corelibs)
