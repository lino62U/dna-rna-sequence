include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_ejemplo test_ejemplo.cpp)

# Si tienes código propio que quieres probar:
target_link_libraries(test_ejemplo gtest_main mi_lib)

include(GoogleTest)
gtest_discover_tests(test_ejemplo)

add_test(NAME test_ejemplo COMMAND test_ejemplo)
