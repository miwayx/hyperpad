# Find Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# Executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hyperpad MANUAL_FINALIZATION)
else()
    add_executable(hyperpad)
endif()

# Link
target_link_libraries(hyperpad PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(hyperpad)
endif()

# Sources
target_sources(hyperpad
    # Headers
    PUBLIC
    mainwindow.hpp

    # Sources
    PRIVATE
    main.cpp
    mainwindow.cpp

    # UI Files

)
