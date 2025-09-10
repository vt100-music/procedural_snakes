cmake_minimum_required(VERSION 3.31)
project(psnakes)

set(CMAKE_CXX_STANDARD 20)

add_executable(psnakes psnakes.cpp
        segment.cpp
        segment.h
        creature.cpp
        creature.h)

include_directories(/usr/local/include)

find_package(SFML 3 COMPONENTS System Window Graphics Network Audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(psnakes SFML::Graphics)