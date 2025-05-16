cmake_minimum_required(VERSION 3.10)
project(sequence_classifier)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# Lógica en una biblioteca (sin main)
add_library(sequence_lib
    src/logic.cpp
)

# Ejecutable principal del programa
add_executable(main_app
    src/app_main.cpp
)
target_link_libraries(main_app PRIVATE sequence_lib)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Ejecutable de tests (sin app_main.cpp)
add_executable(test_runner
    tests/tests.cpp
)
target_link_libraries(test_runner PRIVATE sequence_lib gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(test_runner)
