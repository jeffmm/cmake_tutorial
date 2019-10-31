# Add the test as an executable
add_executable(test_take_two test_take_two.cpp)

# Link to the take_two library and Catch2 testing library
target_link_libraries(test_take_two PRIVATE take_two Catch2::Catch2)

# Add the test to CTest, so it will be run with the 'test' make-target
add_test(NAME take_two_test COMMAND test_take_two)
