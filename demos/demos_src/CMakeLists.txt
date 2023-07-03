
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

 add_definitions(/bigobj)

find_library(SDL2 SDL2.lib SDL2main.lib PATHS ../thirdparty/SDL2-2.0.9/lib/x64)


include_directories(
		../../thirdparty/SDL2-2.0.9/include
		../../src/include
		../../thirdparty/glad/include
		.
)

target_link_libraries (libretti_demos
		libretti
		glad
		${SDL2}

)