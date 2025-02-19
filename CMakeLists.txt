cmake_minimum_required(VERSION 3.15)
project(cppargparse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)


add_executable(${PROJECT_NAME}
    "src/main.cpp"
    "src/argument.cpp"
    "src/converter.cpp"
    "src/parser.cpp"
    "src/types.cpp"
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)
