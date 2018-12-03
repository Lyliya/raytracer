project(raytracer)
cmake_minimum_required(VERSION 2.8.12)

if (UNIX)
  add_definitions("-I . -Wall -Wextra -std=c++17 -D UNIX")
endif (UNIX)

include_directories("${PROJECT_SOURCE_DIR}/src/")

add_executable(raytracer
  src/main.cpp)
