# Take Two v0.2

## Let's create an example executable

Add a folder named `example` to your directory like so

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
├── README.md
├── CMakeLists.txt
└── .gitignore
```

`example/example.cpp` should just be a simple main function that includes the Take Two library
```cpp
#include <take_two/take_two.hpp>
```
and demonstrates its functionality.

The `example/CMakeLists.txt` file should be

```cmake
add_executable(example example.cpp)
target_link_libraries(example PRIVATE take_two)
```

Now add the following line to the end of your top-level `CMakeLists.txt` file:
```cmake
add_subdirectory(example)
```

Now rebuild the project (first remove any prior-existing build folder)
```bash
mkdir build
cd build
cmake ..
make
```

You should now be able to run the example executable in the build folder with

```bash
./example/example
```

