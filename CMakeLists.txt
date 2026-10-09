cmake_minimum_required(VERSION 3.18)

project(finspect)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin")

add_executable(finspect 
    finspect/main.cpp
    finspect/AhoCorasick.cpp
    finspect/IO.cpp
)

target_include_directories(finspect
PRIVATE
    ./
    finspect

)

if (LINUX)
    target_compile_options(finspect
    PRIVATE
        "-g"
    )
endif()