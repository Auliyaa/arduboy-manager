cmake_minimum_required(VERSION 3.26)

# --------------------------------------
# global configuration
# --------------------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------------------------------------
# declare project based on info from vcpkg.json
# --------------------------------------
file(READ "vcpkg.json" VCPKG_JSON)
string(JSON VCPKG_PROJECT_NAME GET "${VCPKG_JSON}" "name")
string(JSON VCPKG_PROJECT_VERSION GET "${VCPKG_JSON}" "version")

project(${VCPKG_PROJECT_NAME}
  VERSION ${VCPKG_PROJECT_VERSION}
  LANGUAGES CXX
)

# --------------------------------------
# install paths
# --------------------------------------
if(WIN32)
  include(cmake/W32InstallDirs.cmake)
endif()

include(GNUInstallDirs)

# --------------------------------------
# Qt / CMake automation
# --------------------------------------
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

# --------------------------------------
# dependencies
# --------------------------------------
find_package(Qt6Core CONFIG REQUIRED)
find_package(Qt6Gui CONFIG REQUIRED)
find_package(Qt6Widgets CONFIG REQUIRED)
find_package(Qt6SerialPort CONFIG REQUIRED)

qt_standard_project_setup()

# --------------------------------------
# arduboy-manager target
# --------------------------------------
add_executable(arduboy-manager
  src/main.cpp
  src/utils.cpp

  include/MainWindow.h
  src/MainWindow.cpp
  ui/MainWindow.ui

  include/GameWidget.h
  src/GameWidget.cpp
  ui/GameWidget.ui
)

target_include_directories(arduboy-manager
  PRIVATE include
)

target_link_libraries(arduboy-manager
  PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::SerialPort
)

set_target_properties(arduboy-manager PROPERTIES
  WIN32_EXECUTABLE ON
)

# --------------------------------------
# install + Qt runtime deployment
# --------------------------------------
# install(TARGETS arduboy-manager
#   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

qt_generate_deploy_app_script(
    TARGET arduboy-manager
    OUTPUT_SCRIPT arduboy_manager_QTDEPLOY_SCRIPT
    NO_UNSUPPORTED_PLATFORM_ERROR
)
qt_finalize_executable(arduboy-manager)

install(TARGETS arduboy-manager BUNDLE DESTINATION .)
install(SCRIPT "${arduboy_manager_QTDEPLOY_SCRIPT}")

install(DIRECTORY share/ DESTINATION share)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  install(PROGRAMS
    ${CMAKE_BINARY_DIR}/zlibd1.dll
    ${CMAKE_BINARY_DIR}/double-conversion.dll
    ${CMAKE_BINARY_DIR}/pcre2-16d.dll
    ${CMAKE_BINARY_DIR}/zstd.dll
    ${CMAKE_BINARY_DIR}/harfbuzz.dll
    ${CMAKE_BINARY_DIR}/libpng16d.dll
    ${CMAKE_BINARY_DIR}/freetyped.dll
    ${CMAKE_BINARY_DIR}/bz2d.dll
    ${CMAKE_BINARY_DIR}/brotlidec.dll
    ${CMAKE_BINARY_DIR}/brotlicommon.dll
    DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
endif()
