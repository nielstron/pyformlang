cmake_minimum_required(VERSION 3.14)

# Download and build GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add test executable
add_executable(cppformlang_tests
  test_main.cpp
  cfg/test_cfg.cpp
  finite_automaton/test_dfa.cpp
  regular_expression/test_regex.cpp
)

# Link against GoogleTest and our library
target_link_libraries(cppformlang_tests
  gtest
  gtest_main
  cppformlang
)

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(cppformlang_tests)