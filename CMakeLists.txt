cmake_minimum_required(VERSION 3.10)
project(C64_Raycaster)

set(CMAKE_CXX_STANDARD 17)
add_compile_options ( -DSFML_STATIC )
include_directories(src)
add_subdirectory(src)

option(BUILD_TEST "Build the unit tests" OFF)
if(BUILD_TEST)
    add_subdirectory(tst)
    add_subdirectory(lib/googletest)
    include_directories(lib/googletest/googletest/include)
    execute_process(COMMAND git submodule update --init --recursive)
endif()

if(WIN32 OR WIN64)
	set(SFML_STATIC_LIBRARIES TRUE)
	set(BUILD_SHARED_LIBS FALSE)
	execute_process(COMMAND git submodule update --init --recursive)
	add_subdirectory(lib/SFML)
endif()

