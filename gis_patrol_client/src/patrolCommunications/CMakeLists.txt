cmake_minimum_required(VERSION 3.7)

project(patrolCommunications VERSION 1.0.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)   # See below (1)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Xml REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(GSL REQUIRED)    # 

include_directories(${PROJECT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${PostgreSQL_INCLUDE_DIRS}
                    ../gis_patrolutils
                    ../dataaccess
                    ../corelibs
                    )

set(HEADERS
    pAttribute.h
    pCommCenter.h
    pCommCenterType.h
    pCommNode.h
    pParameter.h
    pParamType.h
    pParamGroup.h
    pCatParameter.h
    pParamView.h
    pCategory.h
    pCategoryType.h
    pIObject.h
    pParamValue.h
    pRecord.h
    pRecordC.h
    pFilter.h
    pFilterGroup.h
)

set(SOURCES
    pCommCenter.cpp
    pCommCenterType.cpp
    pCommNode.cpp
    pParameter.cpp
    pParamType.cpp
    pParamGroup.cpp
    pCatParameter.cpp
    pParamView.cpp
    pCategory.cpp
    pCategoryType.cpp
    pIObject.cpp
    pParamValue.cpp
    pRecord.cpp
    pRecordC.cpp
    pFilter.cpp
    pFilterGroup.cpp
)

qt5_wrap_ui(UIS_HDRS ${FORMS} )

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Xml ${PostgreSQL_LIBRARIES} ${GSL_LIBRARIES} dataaccess gis_patrolutils)


