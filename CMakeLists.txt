cmake_minimum_required(VERSION 3.20)

project(Lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(logic INTERFACE)

target_sources(logic INTERFACE
        TextEntities.h
        List.h
        SortingAlgorithms.h
        TextAnalyzer.h
)

target_include_directories(logic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Lab1 main.cpp)

target_link_libraries(Lab1 PRIVATE logic)

enable_testing()
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(runTests ${TEST_SOURCES})
target_link_libraries(runTests PRIVATE logic gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)