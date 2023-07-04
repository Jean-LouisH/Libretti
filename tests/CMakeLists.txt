
cmake_minimum_required(VERSION 3.14)

project ("libretti_tests")

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/be03d00f5f0cc3a997d1a368bee8a1fe93651f48.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE libretti_tests_sources "[a-zA-Z]*.cpp")
file(GLOB_RECURSE libretti_tests_headers "[a-zA-Z]*.hpp")

add_executable(libretti_tests
	  ${libretti_tests_sources}
	  ${libretti_tests_headers})

add_dependencies(libretti_tests
	glad
	libretti)

 add_definitions(/bigobj)

find_library(SDL2 SDL2.lib SDL2main.lib PATHS ../thirdparty/SDL2-2.0.9/lib/x64)


include_directories(
		../thirdparty/SDL2-2.0.9/include
		../src/include
		.
)

target_link_libraries (libretti_tests
		libretti
		${SDL2}
		GTest::gtest_main

)

include(GoogleTest)
gtest_discover_tests(libretti_tests)