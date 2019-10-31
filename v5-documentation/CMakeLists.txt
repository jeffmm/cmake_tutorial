# Tested for CMake version 3.7
cmake_minimum_required(VERSION 3.4)

# Project name and a few useful settings. Other commands can pick up the results
project(TakeTwo
    VERSION 0.4
    DESCRIPTION "An example project with CMake"
    LANGUAGES CXX
)

# Only build documentation if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Docs only available if this is the main project
    find_package(Doxygen QUIET)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

# Add any third-party dependencies
add_subdirectory(thirdparty)

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(examples)

# Testing only available if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
