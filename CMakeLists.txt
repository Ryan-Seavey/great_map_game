cmake_minimum_required(VERSION 3.30)
project(HOI5)

set(CMAKE_CXX_STANDARD 23)
find_package(SDL3 REQUIRED)
add_executable(HOI5 main.cpp
        Pixel.h++
        Country.h++
        RyUtil.h++)

target_link_libraries(HOI5 PRIVATE SDL3::SDL3)


