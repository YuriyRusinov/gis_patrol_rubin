cmake_minimum_required(VERSION 3.7)

project(guifactory VERSION 1.0.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)   # See below (1)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Location REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${Qt5Location_INCLUDE_DIRS}
                    ${PostgreSQL_INCLUDE_DIRS}
                    ../../gis_patrolutils
                    ../dataaccess
                    ../../patrolCommunications
                    ../pgui
                    ../pgui/ui
                    ../../corelibs
                    )

qt5_wrap_ui(UIS_HDRS ${FORMS} )

set(HEADERS
    pEntityFactory.h
    pParamGuiFactory.h
    pCatGuiFactory.h
    pIOGuiFactory.h
)

set(SOURCES
    pEntityFactory.cpp
    pParamGuiFactory.cpp
    pCatGuiFactory.cpp
    pIOGuiFactory.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Location gis_patrolutils dataaccess patrolCommunications pgui corelibs)
