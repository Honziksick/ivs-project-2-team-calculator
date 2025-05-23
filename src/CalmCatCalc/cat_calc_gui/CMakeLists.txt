################################################################################
#                                                                              #
# Název projektu:   Calm CatCalc                                               #
#                                                                              #
# Soubor:           CMakeLists.txt                                             #
# Autor:            Lukáš Farkašovský <xfarkal00>                              #
# Datum:            15.04.2024                                                 #
# Poslední změna:   16.04.2024                                                 #
#                                                                              #
# Tým:      Calm CatCalc Coders                                                #
# Členové:  Farkašovský Lukáš    <xfarkal00>                                   #
#           Hýža Pavel           <xhyzapa00>                                   #
#           Kalina Jan           <xkalinj00>                                   #
#           Krejčí David         <xkrejcd00>                                   #
#                                                                              #
# Popis:    Tento CMakeLists.txt slouží ke stavbě kalkulačky 'Calm CatCalc',   #
#           resp. GUI verze této aplikace.                                     #
#                                                                              #
################################################################################

cmake_minimum_required(VERSION 3.5)

project(cat_calc_gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SRC_DIR "../../CalmCatCalc/cat_calc_gui/")
set(CORE_DIR "../../CalmCatCalc/core/")
aux_source_directory("${SRC_DIR}" PROJECT_SOURCES)
aux_source_directory("${CORE_DIR}" PROJECT_SOURCES)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../**" "${CORE_DIR}")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(cat_calc_gui
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET cat_calc_gui APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(cat_calc_gui SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(cat_calc_gui
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(cat_calc_gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.cat_calc_gui)
endif()
set_target_properties(cat_calc_gui PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS cat_calc_gui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(cat_calc_gui)
endif()

# Konec souboru CMakeLists.txt #
