cmake_minimum_required(VERSION 3.12)
project(curves)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    curves
    curves.cpp
    main.cpp
)

target_compile_options(curves PRIVATE -Wall)