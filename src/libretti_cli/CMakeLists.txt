
cmake_minimum_required(VERSION 3.8)

project("libretti_cli")

file(GLOB_RECURSE libretti_cli_sources "[a-zA-Z]*.cpp")
file(GLOB_RECURSE libretti_cli_headers "[a-zA-Z]*.hpp")

add_executable(libretti_cli
	  ${libretti_cli_sources}
	  ${libretti_cli_headers})

add_dependencies(libretti_cli
	libretti)

if (WIN32)
add_definitions(/bigobj)
endif ()

target_include_directories(libretti_cli PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/../libretti/include"
		"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries (libretti_cli
		libretti
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
add_definitions(-D_DEBUG)
endif()