
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE test_oscilloscope_sources "[a-zA-Z]*.cpp")
file(GLOB_RECURSE test_oscilloscope_headers "[a-zA-Z]*.hpp")

add_library(test_oscilloscope STATIC
	  ${test_oscilloscope_sources}
	  ${test_oscilloscope_headers})

add_dependencies(test_oscilloscope
	libretti)

 add_definitions(/bigobj)

find_library(SDL2 SDL2.lib SDL2main.lib PATHS ../../thirdparty/SDL2-2.0.9/lib/x64)


include_directories(
		../../thirdparty/SDL2-2.0.9/include
		../libretti/include
		.
)

target_link_libraries (test_oscilloscope
		libretti
		${SDL2}

)