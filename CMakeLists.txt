cmake_minimum_required(VERSION 3.0)

project(virtpc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES "src/*.cpp")

find_package(Threads REQUIRED)
set (GTEST_ROOT "/usr/local/lib")
set (GTEST_INCLUDE_DIR "/usr/local/lib")
find_package(GTest REQUIRED)

add_executable(virtpc ${SOURCES})

target_compile_options(virtpc PRIVATE -Wall -Wextra -pedantic -Werror -pthread -O2)

target_link_libraries(virtpc PRIVATE 
    Threads::Threads
   GTest::GTest GTest::Main
)

gtest_discover_tests(virtpc)
enable_testing()
set_target_properties(virtpc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/obj"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/obj"
)