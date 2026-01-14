cmake_minimum_required(VERSION 3.31)
project(game_of_life LANGUAGES CXX)

set(CMAKE_CXX_STANDARD            23)
set(CMAKE_CXX_STANDARD_REQUIRED   ON)
set(CMAKE_CXX_EXTENSIONS          OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable ctest before adding any targets and tests
enable_testing()

# FetchContent for gtest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

# Global includes
include(GoogleTest)

# Targets
add_library(logic src/gameOfLife.cpp)
target_include_directories(logic PUBLIC src)

add_executable(game_of_life src/main.cpp)
target_link_libraries(game_of_life PRIVATE logic)

add_executable(test_game_of_life tests/testGameOfLife.cpp)
target_link_libraries(test_game_of_life PRIVATE logic GTest::gtest GTest::gtest_main)

gtest_discover_tests(test_game_of_life)
