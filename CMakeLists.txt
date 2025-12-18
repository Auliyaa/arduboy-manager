cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------------------------------------
# declare project based on info from vcpkg.json
# --------------------------------------
file(READ "vcpkg.json" VCPKG_JSON)
string(JSON VCPKG_PROJECT_NAME GET "${VCPKG_JSON}" "name")
string(JSON VCPKG_PROJECT_VERSION GET "${VCPKG_JSON}" "version")
project(${VCPKG_PROJECT_NAME} VERSION ${VCPKG_PROJECT_VERSION})

# --------------------------------------
# install paths
# --------------------------------------
if(WIN32)
  include(cmake/W32InstallDirs.cmake)
endif(WIN32)
include(GNUInstallDirs)

# --------------------------------------
# dependencies
# --------------------------------------
find_package(Qt6Gui CONFIG REQUIRED)

# --------------------------------------
# arduboy-manager
# --------------------------------------
add_executable(arduboy-manager
  src/main.cpp
)

target_link_libraries(arduboy-manager
  Qt6::Gui
)

install(TARGETS arduboy-manager)