set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find Qt
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Executable
add_executable(hyperpad)

# Link
target_link_libraries(hyperpad PRIVATE
    Qt5::Core
    Qt5::Widgets
)

# Sources
target_sources(hyperpad
    # Headers
    PUBLIC
    mainwindow.hpp
    io.hpp
    texteditor.hpp
    # Sources
    PRIVATE
    main.cpp
    mainwindow.cpp
    io.cpp
    texteditor.cpp
    # UI files
    mainwindow.ui
)
