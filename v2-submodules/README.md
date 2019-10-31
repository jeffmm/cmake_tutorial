# Take Two v0.2

## Let's create a new project that uses TakeTwo as a dependency

Create a new git repository and give it a name like take_two_project

The project structure should look similar to this

```bash
take_two_project
├── src
│   ├── CMakeLists.txt
│   └── take_two.cpp
├── thirdparty
│   └── CMakeLists.txt
├── README.md
├── CMakeLists.txt
└── .gitignore
```

Since take_two_project will only be an executable binary, there is no include folder here.

The top-level CMakeLists.txt file should look like this:

```cmake
cmake_minimum_required(VERSION 3.4)
project(TakeTwoProject
    VERSION 0.1
    DESCRIPTION "A project that uses TakeTwo as a submodule"
    LANGUAGES CXX
)

add_subdirectory(thirdparty)

add_subdirectory(src)
```

The `src/CMakeLists.txt` file should look like this:

```cmake
# Represent all files that end with .cpp with the SOURCES variable
file (GLOB SOURCES "*.cpp")

# Compile sources into an executable binary
add_executable (take_two_project ${SOURCES})

# Link the take_two library to the executable
target_link_libraries (take_two_project take_two)

# Install the executable locally
install(TARGETS take_two_project DESTINATION bin)
```

And your `thirdparty/CMakeLists.txt` file only needs the line:

```cmake
add_subdirectory (take_two)
```

Now we will add the take_two project repository as a submodule for our new project.

```bash
cd thirdparty
git submodule add https://github.com/<your_github_username>/take_two.git take_two
```

This will clone your take_two project repository into the `thirdparty` folder, and register take_two as a submodule in a newly-created `.gitmodules` file.

Note: the take_two_project repo will **not** track the submodule's files, but instead tracks a pointer to a single commit in the submodule repository. By default, this commit is the most recent commit on the submodule's master branch. You can choose to track a different branch using the command `git submodule add -b <branch_name> <repo_url> <local_folder>`.

In my example case here, my submodule is pointing to a branch named `submodule` in this same repository, which is identical to the contents of the `v1-cmake-intro` folder.

Now we can compose a simple main function that utilizes the take_two library. For example, my `src/take_two_project.cpp` file looks like this:

```cpp
#include <iostream>
#include <take_two/take_two.hpp>

int main() {
  std::cout << "12 + 21 = " << TakeTwo::Add(12, 21) << std::endl;
  return 0;
}
```

Now all that's left to do is compile and run the binary.

```bash
mkdir build
cd build
cmake ..
make
```

The `take_two_project` binary will be built inside `src` folder in the `build` folder, and can be executed with

```bash
./src/take_two_project
```

Or we can install the binary locally with

```bash
make install
```

And run the executable anywhere as long as the install location is in our PATH

```bash
take_two_project
```
