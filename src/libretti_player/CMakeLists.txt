
cmake_minimum_required(VERSION 3.8)

project("libretti_player")

add_subdirectory("thirdparty")

file(GLOB_RECURSE libretti_player_sources "[a-zA-Z]*.cpp")
file(GLOB_RECURSE libretti_player_headers "[a-zA-Z]*.hpp")

add_definitions(-DLIBRETTI_DEMOS_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/../libretti/data/demos/")

find_package(SDL2 REQUIRED)

add_executable(libretti_player
	  ${libretti_player_sources}
	  ${libretti_player_headers})

add_dependencies(libretti_player
	glad
	libretti)

if (WIN32)
add_definitions(/bigobj)
endif ()

target_include_directories(libretti_player PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../libretti/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include"
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries (libretti_player
		libretti
		SDL2::SDL2
		glad
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
add_definitions(-D_DEBUG)
endif()