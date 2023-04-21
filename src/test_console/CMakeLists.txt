
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE test_console_sources "[a-zA-Z]*.cpp")
file(GLOB_RECURSE test_console_headers "[a-zA-Z]*.hpp")

add_executable(test_console
	  ${test_console_sources}
	  ${test_console_headers})

add_dependencies(test_console
	#test_oscilloscope
	libretti)

 add_definitions(/bigobj)

find_library(SDL2 SDL2.lib SDL2main.lib PATHS ../../thirdparty/SDL2-2.0.9/lib/x64)


include_directories(
		../../thirdparty/SDL2-2.0.9/include
		../libretti/include
		#../test_oscilloscope
		.
)

target_link_libraries (test_console
		libretti
		#test_oscilloscope
		${SDL2}

)