# Add the test as an executable
add_executable(test_take_two test_take_two.cpp)

# Link to the TakeTwo library and Catch2 testing library
target_link_libraries(test_take_two PRIVATE TakeTwo Catch2::Catch2)

# Add the test to CTest, so it will be run with the 'test' make-target
add_test(NAME TakeTwo_test COMMAND test_take_two)
