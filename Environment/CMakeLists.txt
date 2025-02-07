cmake_minimum_required(VERSION 3.24.2)
project(cpp)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_STANDARD 20)

set(GCC_COVERAGE_COMPILE_FLAGS "−Wall -Wl")
set(CMAKE_C_FLAGS "-static -lm -DONLINE_JUDGE -DBOJ -Wall -Wl,--stack=268435456 -O2 -std=gnu++17")
add_compile_definitions(LOCAL)

add_executable(cpp main.cpp debug.h)

target_include_directories(cpp PRIVATE /usr/local/include)

set_target_properties(cpp
        PROPERTIES
        OSX_ARCHITECTURES "arm64"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        PREFIX ""
        )
