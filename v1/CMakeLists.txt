# Tested for CMake version 3.4+
cmake_minimum_required(VERSION 3.4)

# Project name and a few useful settings.
project(TakeTwo
    VERSION 0.1
    DESCRIPTION "An example project with CMake"
    LANGUAGES CXX
)

# The library source code is here
add_subdirectory(src)
