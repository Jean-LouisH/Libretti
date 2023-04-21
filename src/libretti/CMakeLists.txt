
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE libretti_sources "[a-zA-Z]*.c")
file(GLOB_RECURSE libretti_headers "include/[a-zA-Z]*.h")

add_library(libretti SHARED
	  ${libretti_sources}
	  ${libretti_headers})

 add_definitions(/bigobj)

find_library(SDL2 SDL2.lib SDL2main.lib PATHS ../../thirdparty/SDL2-2.0.9/lib/x64)


include_directories(
		../../thirdparty/SDL2-2.0.9/include
		./include
)

target_link_libraries (libretti
		${SDL2}

)

add_definitions(-D_LIBRETTI_EXPORTS)

add_custom_command(TARGET libretti POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:libretti> ${PROJECT_BINARY_DIR}/src/test_console/libretti.dll
)