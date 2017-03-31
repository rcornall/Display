cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

project(display)

# for vim c++ completion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

if(NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(BUILD_SHARED_LIBS true)

set(COMPILER_FLAGS "-ansi -Wall -pedantic -Wextra -Weffc++")
set(CMAKE_CXX_FLAGS "${COMPILER_FLAGS}")

set(display_INCLUDE_DIRS "inc/display" CACHE INTERNAL "")
set(DISPLAY display CACHE INTERNAL "")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)

