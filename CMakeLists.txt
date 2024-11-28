cmake_minimum_required(VERSION 3.14)

project(SquareMatrix)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src/square_matrix src/utils)

set(SOURCES src/square_matrix/square_matrix.cpp src/utils/utils.cpp src/main.cpp)

add_executable(SquareMatrix ${SOURCES})

# Compile with all warnings, treat warnings as errors
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
