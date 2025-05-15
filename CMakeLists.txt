cmake_minimum_required(VERSION 3.14)
project(TuProyecto)

set(CMAKE_CXX_STANDARD 17)

# Incluir directorios fuente y headers
include_directories(include)
add_subdirectory(src)
add_subdirectory(tests)
