# Tested for CMake version 3.4+
cmake_minimum_required(VERSION 3.4)

# Project name and a few useful settings. Other commands can pick up the results
project(TakeTwo
    VERSION 0.3
    DESCRIPTION "An example project with CMake"
    LANGUAGES CXX
)

# Add any third-party dependencies
add_subdirectory(thirdparty)

# The compiled library code is here
add_subdirectory(src)

# The executable example code is here
add_subdirectory(examples)

# Testing only available if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
