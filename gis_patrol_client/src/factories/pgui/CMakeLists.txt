cmake_minimum_required(VERSION 3.7)

project(pgui VERSION 1.0.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)   # See below (1)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Svg REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${PostgreSQL_INCLUDE_DIRS}
                    ../../gis_patrolutils
                    ../../dataaccess
                    ../../corelibs
                    ../../patrolCommunications
                    )

qt5_wrap_ui(UIS_HDRS ${FORMS} )

set(HEADERS
    pParamListForm.h
    pCategoryListForm.h
    pParamModel.h
    pTreeItem.h
    pCatTreeItem.h
    pCategoryModel.h
    pCatParamModel.h
    pCatEditor.h
    pCatParamSortModel.h
    pItemDelegate.h
    pCatParamDelegate.h
    pCIOEditor.h
    pRecordDataModel.h
    pRecTreeItem.h
    pAbstractParamWidget.h
    pCheckBox.h
    pRefLineEdit.h
    pLineEdit.h
    pDateEdit.h
    pDateTimeEdit.h
    pTimeEdit.h
    pTextEdit.h
    pColorEdit.h
    pSVGWidget.h
    pRecWidget.h
    pXMLEdit.h
    pCheckableDataModel.h
    pParamCheckWidget.h
    pEventFilter.h
    pImageLabel.h
    pGeomForm.h
    pSettingsDelegate.h
    ui/paramsgroupform.h
    ui/paramsform.h
    ui/precdialog.h
    ui/psearchform.h
)

set(FORMS
    ui/params_group_form.ui
    ui/params_form.ui
    ui/p_rec_dialog.ui
    ui/p_search_form.ui
)

set(SOURCES
    pCategoryListForm.cpp
    pParamListForm.cpp
    pParamModel.cpp
    pTreeItem.cpp
    pCatTreeItem.cpp
    pCategoryModel.cpp
    pCatParamModel.cpp
    pCatEditor.cpp
    pCatParamSortModel.cpp
    pItemDelegate.cpp
    pCatParamDelegate.cpp
    pCIOEditor.cpp
    pRecordDataModel.cpp
    pRecTreeItem.cpp
    pAbstractParamWidget.cpp
    pCheckBox.cpp
    pRefLineEdit.cpp 
    pLineEdit.cpp
    pDateEdit.cpp
    pDateTimeEdit.cpp
    pTimeEdit.cpp
    pTextEdit.cpp
    pColorEdit.cpp
    pSVGWidget.cpp
    pRecWidget.cpp
    pXMLEdit.cpp
    pCheckableDataModel.cpp
    pParamCheckWidget.cpp
    pEventFilter.cpp
    pImageLabel.cpp
    pGeomForm.cpp
    pSettingsDelegate.cpp
    ui/paramsgroupform.cpp
    ui/paramsform.cpp
    ui/precdialog.cpp
    ui/psearchform.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Svg gis_patrolutils patrolCommunications)


