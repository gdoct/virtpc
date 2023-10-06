cmake_minimum_required(VERSION 3.0)

project(virtualpc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# file(GLOB_RECURSE SOURCES "src/*.cpp")

find_package(Threads REQUIRED)

file(GLOB_RECURSE SOURCES 
    "src/*/*.cpp"
    "src/*/*.h"
)

file(GLOB_RECURSE TESTS 
    "test/*.h"
    "test/*.cpp"
)

# virtlib.o
add_library(virt ${SOURCES})
target_link_libraries(virt PRIVATE Threads::Threads)
set_target_properties(virt PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib
)

# virtpc
add_executable(virtpc
    src/main.cpp
)

target_link_libraries(virtpc PRIVATE virt)

set_target_properties(virtpc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin
)

# virtpc-tests
add_executable(virtpc-tests ${TESTS})
set_target_properties(virtpc-tests PROPERTIES EXCLUDE_FROM_ALL TRUE)

target_link_libraries(virtpc-tests PRIVATE virt)

set_target_properties(virtpc-tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(virtpc-tests PRIVATE -Wall -Wextra -pedantic -Werror -pthread -O2)
    target_compile_options(virtpc PRIVATE -Wall -Wextra -pedantic -Werror -pthread -O2)
    target_compile_options(virt PRIVATE -Wall -Wextra -pedantic -Werror -pthread -O2)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(virt PRIVATE /std:c++20 )
    target_compile_options(virtpc PRIVATE /std:c++20 )
    target_compile_options(virtpc-tests PRIVATE /std:c++20 )
endif()

configure_file(src/microcode.dat ${CMAKE_CURRENT_BINARY_DIR}/microcode.dat COPYONLY)

add_custom_target(unittests)
add_dependencies(unittests virtpc-tests virt)

enable_testing()
add_test(NAME logger COMMAND build/bin/virtpc-tests LoggerTests)
add_test(NAME machine COMMAND build/bin/virtpc-tests MachineTests)
add_test(NAME memory COMMAND build/bin/virtpc-tests MemoryTests)
add_test(NAME cpu COMMAND build/bin/virtpc-tests CpuTests)
add_test(NAME clock COMMAND build/bin/virtpc-tests ClockTests)
add_test(NAME microcode COMMAND build/bin/virtpc-tests MicrocodeTests)
add_test(NAME executionengine COMMAND build/bin/virtpc-tests ExecutionEngineTests)
