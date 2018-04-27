cmake_minimum_required(VERSION 3.9)
project(buscaminas)

set(CMAKE_CXX_STANDARD 11)

add_executable(buscaminas main.cpp tablero.cpp tablero.h)

target_link_libraries(buscaminas ncursesw)