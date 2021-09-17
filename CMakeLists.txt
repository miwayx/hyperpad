cmake_minimum_required(VERSION 3.5)

project(hyperpad LANGUAGES CXX VERSION 0.50)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Version Configure
configure_file (
    "src/version.h.in"
    "version.h"
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# Executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hyperpad MANUAL_FINALIZATION)
else()
    add_executable(hyperpad)
endif()

# Sources
cmake_policy(SET CMP0076 NEW)
target_sources(hyperpad
    # Headers
    PUBLIC
    src/mainwindow.hpp
    # Sources
    PRIVATE
    src/main.cpp
    src/mainwindow.cpp
    # UI Files
    src/mainwindow.ui
    # Resources
    src/resources.qrc
)

# Link
target_link_libraries(hyperpad PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(hyperpad)
endif()

# Install Files
include(GNUInstallDirs)
install(TARGETS hyperpad RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES assets/application/hyperpad.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES CONTRIBUTING.md DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/hyperpad/)
install(FILES README.md DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/hyperpad/)
install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/hyperpad/)
install(FILES src/res/hyper_ico.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pixmaps RENAME hyperpad.png)




