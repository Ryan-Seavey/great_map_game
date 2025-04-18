cmake_minimum_required(VERSION 3.30)
project(HOI5)

set(CMAKE_CXX_STANDARD 23)
find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
add_executable(HOI5 main.cpp
        Pixel.h++
        Country.h++
        RyUtil.h++
        AI/AI_Contract.hpp
        AI/prototypes/AI_dumb.hpp
        AI/prototypes/AI_dumb.cpp
        AI/prototypes/AI_peaceful.c++
        AI/prototypes/AI_peaceful.h++
        facets/Economy.h++
        facets/Military.c++
        facets/Military.h++
        facets/Government.h++)

target_link_libraries(HOI5 PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)


