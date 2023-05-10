# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("libretti")
project ("libretti_tests")

# Include sub-projects.
add_subdirectory("src")
add_subdirectory("tests")
add_subdirectory("thirdparty")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests)