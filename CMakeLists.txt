cmake_minimum_required(VERSION 3.5)

project(hyperpad LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# Ui Files
qt_wrap_ui(PROJECT_SOURCES
    src/mainwindow.ui
)
# Resources Files
qt_add_resources(PROJECT_SOURCES
    src/resources.qrc
)

# Executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hyperpad MANUAL_FINALIZATION)
else()
    add_executable(hyperpad)
endif()

# Sources
target_sources(
    # Sources
    PRIVATE
    src/main.cpp
    src/mainwindow.cpp
    # Headers
    PUBLIC
    src/mainwindow.hpp
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
install(FILES src/res/hyperpad_ico.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pixmaps RENAME hyperpad.png)




