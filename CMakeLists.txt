cmake_minimum_required(VERSION 3.5)

project(qtext LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Policy for .cc and .hh files
cmake_policy(SET CMP0100 NEW)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# Sources
set(PROJECT_SOURCES
    src/main.cc
    src/mainwindow.cc
    src/mainwindow.hh
)
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
    qt_add_executable(qtext MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
    add_executable(qtext ${PROJECT_SOURCES})
endif()

# Link
target_link_libraries(qtext PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qtext)
endif()

# Install Files
include(GNUInstallDirs)
install(TARGETS qtext RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES assets/application/qtext.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES CONTRIBUTING.md DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/qtext/)
install(FILES README.md DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/qtext/)
install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/qtext/)
install(FILES src/res/qtext_ico.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pixmaps RENAME qtext.png)




