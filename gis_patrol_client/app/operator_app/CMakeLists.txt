cmake_minimum_required(VERSION 3.7)

project(operator_app VERSION 1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    #${gis_patrolutils_INCLUDE_DIRS}
                    #${corelibs_INCLUDE_DIRS}
                    )

set(HEADERS
    patrolmainwindow.h
)

set(FORMS
    patrol_main_window.ui
)

set(SOURCES
    patrolmainwindow.cpp
    main.cpp
)
set(RESOURCES
    ../../src/patrol_icons/patrol.qrc
    ../../gis_patrol.qrc
)

qt5_wrap_ui(UIS_HDRS ${FORMS} )

include_directories(../../src ../../src/corelibs ../../src/factories/guifactory ../../src/patrolCommunications ../../src/factories/pgui )

find_package(GSL REQUIRED)    # See below (2)
find_package(PostgreSQL REQUIRED)

link_directories(${CMAKE_SOURCE_DIR}/build/src)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../gis_patrol_rubin/gis_patrol_client)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../gis_patrol_rubin/gis_patrol_client/src/)
link_directories(${CMAKE_SOURCE_DIR}/build/gis_patrol_rubin/gis_patrol_client/src/corelibs)
#message(STATUS "patrol link dir is ${CMAKE_SOURCE_DIR}/build/gis_patrol_rubin/gis_patrol_client/src/corelibs")
#message(STATUS "corelibs include dir is ${corelibs_INCLUDE_DIRS}")
#message(STATUS "gis_patrolutils include dir is ${gis_patrolutils_INCLUDE_DIRS}")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UIS_HDRS} ${RESOURCES}  )

target_link_libraries(${PROJECT_NAME} Qt5::Widgets GSL::gsl GSL::gslcblas ${PostgreSQL_LIBRARIES} dataaccess corelibs pgui guifactory )

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
)
