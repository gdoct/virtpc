cmake_minimum_required(VERSION 3.16)
project(virtpc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SOURCES
    src/*/*.cpp
)

foreach(SOURCE_FILE ${SOURCES})
    file(RELATIVE_PATH RELATIVE_SOURCE_FILE ${CMAKE_SOURCE_DIR}/src ${SOURCE_FILE})
    get_filename_component(SOURCE_DIR ${RELATIVE_SOURCE_FILE} DIRECTORY)
    string(REPLACE "/" ";" SOURCE_DIR_LIST ${SOURCE_DIR})
    string(REPLACE ";" "/" OBJECT_DIR ${CMAKE_BINARY_DIR}/obj/${SOURCE_DIR_LIST})
    string(REPLACE ".cpp" ".o" OBJECT_FILE ${OBJECT_DIR}/${RELATIVE_SOURCE_FILE})
    add_custom_command(
        OUTPUT ${OBJECT_FILE}
        COMMAND ${CMAKE_CXX_COMPILER} -c ${SOURCE_FILE} -o ${OBJECT_FILE}
        DEPENDS ${SOURCE_FILE}
        COMMENT "Building ${OBJECT_FILE}"
        VERBATIM
    )
    list(APPEND OBJECTS ${OBJECT_FILE})
endforeach()
add_custom_target(objects DEPENDS ${OBJECTS})
add_executable(virtpc ${SOURCES})
add_dependencies(virtpc objects)
set_target_properties(virtpc PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
