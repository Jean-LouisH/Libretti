# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

project ("libretti")

enable_testing()

# Include sub-projects.
add_subdirectory("demos/demos_src")
add_subdirectory("src")
add_subdirectory("thirdparty")
