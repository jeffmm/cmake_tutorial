# Using CMake to install Catch2 as a submodule. Typically we would only have
# one header file include/catch.hpp in the catch2 folder and include it from
# the tests folder.

# Add catch2 only if we are building tests
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND TESTS)
    add_subdirectory(catch2)
endif()
