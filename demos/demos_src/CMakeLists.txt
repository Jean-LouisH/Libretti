
cmake_minimum_required(VERSION 3.8)

project("libretti_demos")

file(GLOB_RECURSE libretti_demos_sources "[a-zA-Z]*.cpp")
file(GLOB_RECURSE libretti_demos_headers "[a-zA-Z]*.hpp")

add_executable(libretti_demos
	  ${libretti_demos_sources}
	  ${libretti_demos_headers})

add_dependencies(libretti_demos
	glad
	libretti)

if (WIN32)
add_definitions(/bigobj)
endif ()

target_include_directories(libretti_demos PRIVATE
		../../thirdparty/SDL2/include
		../../src/include
		../../thirdparty/glad/include
		.
)

target_link_libraries (libretti_demos
		libretti
		glad
		SDL2

)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
add_definitions(-D_DEBUG)
endif()