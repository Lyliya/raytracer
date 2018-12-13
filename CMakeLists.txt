cmake_minimum_required(VERSION 3.9)
project(raytracer VERSION 0.1)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
add_definitions("-D_GLIBCXX_USE_CXX11_ABI=0")

if (UNIX)
	add_definitions("-I ./src/ -Wall -Wextra -D UNIX -std=c++17")
else (UNIX)
	add_definitions("/std:c++17 -D_WIN32_WINNT=0x0501 -D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING")
endif (UNIX)

include_directories("${PROJECT_SOURCE_DIR}/src/")

add_executable(raytracer
  src/main.cpp
  src/Raytracer.cpp
  src/Utils.cpp
  src/Vect.cpp)

set_target_properties(raytracer PROPERTIES VERSION ${PROJECT_VERSION})