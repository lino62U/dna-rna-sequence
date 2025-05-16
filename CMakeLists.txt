cmake_minimum_required(VERSION 3.10)
project(sequence_classifier)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# Agregar archivos fuente
add_library(sequence_lib
    src/main.cpp
)

# Test executable con nombre diferente para evitar conflicto con carpeta 'tests'
add_executable(test_runner
    tests/tests.cpp
)

target_link_libraries(test_runner PRIVATE sequence_lib)

# Copiar archivo sequences.txt al directorio build después de compilar tests
add_custom_command(TARGET test_runner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/tests/sequences.txt ${CMAKE_BINARY_DIR}/sequences.txt
)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(test_runner PRIVATE gtest gtest_main)
