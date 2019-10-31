# TakeTwo v0.4

## Let's add documentation with Doxygen

Add a folder named `docs` to the top-level directory like so

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
├── thirdparty
│   ├── CMakeLists.txt
│   └── catch2
├── tests
│   ├── CMakeLists.txt
│   └── test_take_two.cpp
├── docs
│   ├── CMakeLists.txt
│   └── main.md
├── README.md
├── CMakeLists.txt
└── .gitignore
```

The `docs/CMakeLists.txt` file will assist in building your project's documentation using [Doxygen](http://www.doxygen.nl). You can install doxygen using your package manager from the command line (apt for Ubuntu, homebrew for Mac, etc). The `docs/CMakeLists.txt` file should be:

```cmake
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

doxygen_add_docs(docs
    take_two/take_two.hpp
    "${CMAKE_CURRENT_SOURCE_DIR}/main.md"
    WORKING_DIRECTORY
    "${PROJECT_SOURCE_DIR}/include"
)
```

And your `docs/main.md` file should be a markdown document containing the introduction to your documentation, with the `{#mainpage}` tag on the title, like so

```md
# TakeTwo Documentation {#mainpage}

This is the documentation for my TakeTwo library.

...
```

Now add the following lines to your top-level `CMakeLists.txt` file:

```cmake
# Only build documentation if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Docs only available if this is the main project
    find_package(Doxygen QUIET)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
endif()
```

Now we need to write the documentation itself using the Doxygen syntax. In my example, I document the `TakeTwo` class and its method functions like so

```cpp
/// Take two floating point numbers and perform some simple arithmetic.
/** This class allows for the computation of trivial arithmetic on two numbers.
 */
class TakeTwo {
public:
  /// Add two numbers.
  /**
    \param a the first argument.
    \param b the second argument.
    \return A float a added to b
  */
  static float Add(float a, float b);
}
```

When you are building your project, you can now build the documentation using the `docs` make target, assuming you have doxygen installed

```bash
mkdir build
cd build
cmake ..
make docs
```

Now check out your automatically-generated html documentation by opening `build/docs/html/index.html` in your web browser.
