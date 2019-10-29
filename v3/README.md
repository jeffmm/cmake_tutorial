# Take Two v0.3

## Let's add some unit tests

Add a folder named `tests` to your directory like so

```bash
take_two
├── include
│   └── take_two
│       └── take_two.hpp
├── src
│   ├── CMakeLists.txt
│   └── take_two.cpp
├── example
│   ├── CMakeLists.txt
│   └── example.cpp
├── tests
│   ├── CMakeLists.txt
│   └── test_take_two.cpp
├── README.md
├── CMakeLists.txt
└── .gitignore
```

`tests/test_take_two.cpp` will utilize the Catch2 C++ test library 

```cpp
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <take_two/take_two.hpp>

TEST_CASE("TakeTwo test") {
  // Write your tests here, e.g.:
  SECTION("Addition") {
    REQUIRE(TakeTwo::Add(1, 9) == 10);
    REQUIRE(TakeTwo::Add(-9, 9) == 0);
  }
}
```

The file `tests/CMakeLists.txt` will be

```cmake
add_subdirectory(catch2)

add_executable(test_take_two test_take_two.cpp)

target_link_libraries(test_take_two PRIVATE take_two Catch2::Catch2)

add_test(NAME take_two_test COMMAND test_take_two)
```

Notice that we are including a subdirectory called `catch2` that does not yet exist. The only thing left to do is to add Catch2 as a submodule to the project.

```bash
cd tests
git submodule add https://github.com/catchorg/Catch2 catch2
```

This will clone the Catch2 repository into the `tests` folder as a submodule. Now we need to change the top-level `CMakeLists.txt` file to optionally include the unit tests in the build. Add the following to the end of the file:

```cmake
# Testing only available if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
```

Now remove any existing build folder and build the project and run the unit tests with

```bash
mkdir build
cd build
cmake -DTESTS=TRUE ..
make
make test
```

If everything goes well, all tests should pass. These unit tests will be how we implement continuous integration later on.
