cmake_minimum_required(VERSION 3.26)
project(2048_2)

set(CMAKE_CXX_STANDARD 17)
link_libraries(libeasyx.a libgdi32.a libole32.a)
add_executable(2048_2 main.cpp)
