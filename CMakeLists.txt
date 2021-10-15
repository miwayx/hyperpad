cmake_minimum_required(VERSION 3.5)

project(hyperpad VERSION 0.50)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Version configuration
configure_file (
    "${CMAKE_SOURCE_DIR}/src/version.hpp.in"
    "${CMAKE_SOURCE_DIR}/src/version.hpp"
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source configuration
add_subdirectory(src)

# Install Files only on GNU/Linux
#if(UNIX AND NOT APPLE)
    #include(GNUInstallDirs)
#    install(TARGETS hyperpad RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
#    install(FILES assets/application/hyperpad.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
#    install(FILES CONTRIBUTING.md DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/hyperpad/)
#    install(FILES README.md DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/hyperpad/)
#    install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/hyperpad/)
#    install(FILES src/res/hyper_ico.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pixmaps RENAME hyperpad.png)
#endif()



