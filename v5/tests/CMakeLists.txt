# Let's use CMake to install Catch2 as a submodule (NEVER ACTUALLY DO THIS!)
# Typically we would just include the single catch.hpp header file in the tests folder
add_subdirectory(catch2)

add_executable(test_take_two test_take_two.cpp)

# Should be linked to the take_two library, as well as the Catch2 testing library
target_link_libraries(test_take_two PRIVATE take_two Catch2::Catch2)

add_test(NAME take_two_test COMMAND test_take_two)
