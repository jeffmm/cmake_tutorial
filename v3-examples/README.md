# Take Two v0.2

## Let's create an example executable

Add a folder named `examples` to your directory like so

```bash
take_two
├── include
│   └── take_two
│       └── take_two.hpp
├── src
│   ├── CMakeLists.txt
│   └── take_two.cpp
├── examples
│   ├── CMakeLists.txt
│   └── example.cpp
├── README.md
├── CMakeLists.txt
└── .gitignore
```

`examples/example.cpp` should just be a simple main function that includes the take_two library and demonstrates its functionality:
```cpp
#include <take_two/take_two.hpp>

int main() {
  \\ ...
  \\ Some TakeTwo usage code here
  \\ ...
  return 0;
}
```

The `examples/CMakeLists.txt` file should be

```cmake
add_executable(example example.cpp)
target_link_libraries(example PRIVATE take_two)
```

Now add the following line to the bottom of your top-level `CMakeLists.txt` file:
```cmake
add_subdirectory(examples)
```

Be sure to add and commit your changes:

```bash
git add -A
git commit -m "Added example binary"
```

Now rebuild the project (first remove any previously-existing build folder)
```bash
mkdir build
cd build
cmake ..
make
```

You should now be able to run the example executable in the build folder with

```bash
./examples/example
```
