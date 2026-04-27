
cmake_minimum_required(VERSION 3.8)

project("libretti_player")

add_subdirectory("thirdparty")

file(GLOB_RECURSE libretti_player_sources "[a-zA-Z]*.cpp")
file(GLOB_RECURSE libretti_player_headers "[a-zA-Z]*.hpp")

add_definitions(-DLIBRETTI_DEMOS_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/../libretti/data/demos/")

add_executable(libretti_player
	  ${libretti_player_sources}
	  ${libretti_player_headers})

add_dependencies(libretti_player
	glad
	libretti)

if (MSVC)
	add_definitions(/bigobj)
else ()
	if (MINGW)
		target_compile_options(libretti_player PRIVATE "-Wa,-mbig-obj")
	endif ()
endif ()

if(MINGW AND CMAKE_CROSSCOMPILING)
	set(MINGW_BIN "/usr/x86_64-w64-mingw32/sys-root/mingw/bin")

	set(MINGW_RUNTIME_DEPS
		"${MINGW_BIN}/libgcc_s_seh-1.dll"
		"${MINGW_BIN}/libwinpthread-1.dll"
		"${MINGW_BIN}/libstdc++-6.dll"
	)

	add_custom_command(TARGET libretti_player POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${MINGW_RUNTIME_DEPS}
		${PROJECT_BINARY_DIR}
		COMMENT "Deploying Windows/MinGW Runtime DLLs..."
	)
endif()

target_include_directories(libretti_player PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../libretti/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include"
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

find_package(SDL2 REQUIRED)

target_link_libraries (libretti_player
		libretti
		glad
		SDL2::SDL2
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
add_definitions(-D_DEBUG)
endif()