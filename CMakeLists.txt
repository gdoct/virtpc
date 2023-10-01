cmake_minimum_required(VERSION 3.0)

project(virtualpc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# file(GLOB_RECURSE SOURCES "src/*.cpp")

find_package(Threads REQUIRED)

file(GLOB_RECURSE SOURCES 
    "src/core/*.cpp"
    "src/util/*.cpp"
    "src/microcode/*.cpp"
)

file(GLOB_RECURSE TESTS 
    "test/*.h"
    "test/*.cpp"
)

# virtlib.o
add_library(virt ${SOURCES})
target_link_libraries(virt PRIVATE Threads::Threads)
target_compile_options(virt PRIVATE -Wall -Wextra -pedantic -Werror -pthread -O2)
set_target_properties(virt PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib
)

# virtpc
add_executable(virtpc
    src/main/main.cpp
)

target_link_libraries(virtpc PRIVATE virt)
target_compile_options(virtpc PRIVATE -Wall -Wextra -pedantic -Werror -pthread -O2)
set_target_properties(virtpc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin
)

# virtpc-tests
add_executable(virtpc-tests ${TESTS})

target_link_libraries(virtpc-tests PRIVATE virt)
target_compile_options(virtpc-tests PRIVATE -Wall -Wextra -pedantic -Werror -pthread -O2)
set_target_properties(virtpc-tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin
)
