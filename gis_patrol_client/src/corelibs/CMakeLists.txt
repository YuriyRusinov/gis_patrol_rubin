cmake_minimum_required(VERSION 3.7)

project(corelibs VERSION 1.0.0)
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
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(GSL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${PostgreSQL_INCLUDE_DIRS}
                    ${GSL_INCLUDE_DIRS}
                    ../gis_patrolutils
                    ../dataaccess
                    ../factories/pgui
                    ../factories/guifactory
                    ../patrolCommunications
                    )

qt5_wrap_ui(UIS_HDRS ${FORMS} )

set(HEADERS
    patrolsingleton.h
    patroldbloader.h
    patrolguiapp.h
    patroldbwriter.h
    psettings.h
    ui/logindbform.h
    ui/psettingsform.h
)

set(FORMS
    ui/login_db_form.ui
    ui/p_settings_form.ui
)

set(SOURCES
    patrolsingleton.cpp
    patroldbloader.cpp
    patrolguiapp.cpp
    patroldbwriter.cpp
    psettings.cpp
    ui/logindbform.cpp
    ui/psettingsform.cpp
)

link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src/patrolCommunications)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets ${PostgreSQL_LIBRARIES} ${GSL_LIBRARIES} patrolCommunications guifactory)
