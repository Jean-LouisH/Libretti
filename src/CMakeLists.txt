
cmake_minimum_required (VERSION 3.8)

if (WIN32)
   set(STATIC_LIBRARY_EXTENSION "lib")
   set(SHARED_LIBRARY_EXTENSION "dll")
   set(LIBRARY_PREFIX "")
else()
	set(STATIC_LIBRARY_EXTENSION "a")
	set(SHARED_LIBRARY_EXTENSION "so")
	set(LIBRARY_PREFIX "lib")
endif()

file(GLOB_RECURSE libretti_sources "[a-zA-Z]*.c")
file(GLOB_RECURSE libretti_headers "include/[a-zA-Z]*.h")

add_library(libretti STATIC
	  ${libretti_sources}
	  ${libretti_headers})


find_package(SDL2 REQUIRED)

if (WIN32)
add_definitions(/bigobj)
endif ()

target_include_directories(libretti PUBLIC
		./include
)

target_link_libraries (libretti
	SDL2::SDL2
)

#add_definitions(-D_LIBRETTI_EXPORTS)
add_definitions(-D_LIBRETTI_EXPORTS_BUILD)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
add_definitions(-D_DEBUG)
endif()

add_custom_command(TARGET libretti POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:libretti> ${PROJECT_BINARY_DIR}/demos/demos_src/${LIBRARY_PREFIX}libretti.${SHARED_LIBRARY_EXTENSION}
)