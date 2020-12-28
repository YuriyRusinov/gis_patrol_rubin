cmake_minimum_required(VERSION 3.7)

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

qt5_wrap_ui(UIS_HDRS ${FORMS} )


