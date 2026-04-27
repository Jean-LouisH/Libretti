
cmake_minimum_required(VERSION 3.8)

project("libretti_cli")

file(GLOB_RECURSE libretti_cli_sources "[a-zA-Z]*.cpp")
file(GLOB_RECURSE libretti_cli_headers "[a-zA-Z]*.hpp")

add_executable(libretti_cli
	  ${libretti_cli_sources}
	  ${libretti_cli_headers})

add_dependencies(libretti_cli
	libretti)

if (MSVC)
	add_definitions(/bigobj)
else ()
	if (MINGW)
		target_compile_options(libretti_cli PRIVATE "-Wa,-mbig-obj")
	endif ()
endif ()


if(MINGW AND CMAKE_CROSSCOMPILING)
	set(MINGW_BIN "/usr/x86_64-w64-mingw32/sys-root/mingw/bin")

	set(MINGW_RUNTIME_DEPS
		"${MINGW_BIN}/libgcc_s_seh-1.dll"
		"${MINGW_BIN}/libwinpthread-1.dll"
		"${MINGW_BIN}/libstdc++-6.dll"
	)

	add_custom_command(TARGET libretti_cli POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${MINGW_RUNTIME_DEPS}
		${PROJECT_BINARY_DIR}
		COMMENT "Deploying Windows/MinGW Runtime DLLs..."
	)
endif()

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