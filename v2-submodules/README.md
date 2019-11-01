# TakeTwoProject v0.1

## Let's create a new project that uses TakeTwo as a dependency

In this project, we will include TakeTwo as a submodule in the parent project TakeTwoProject. Submodules are useful when
* The submodule code and project code are part of a common codebase or suite that should be shipped together
* The submodule code is not slow to compile
* The submodule code is not a common dependency that a developer would expect their clients to install

Submodules should not be used for libraries that are very large and cumbersome to install, or if the library can be easily installed using a package manager.

As we will see later, containers can offer the best of both worlds, allowing developers to ship their pre-compiled library dependencies within a Docker image, with the disadvantage of requiring users to have Docker installed.

Create a new git repository and give it a name like `take_two_project`.

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

The top-level `CMakeLists.txt` file should look like this:

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

# Link the TakeTwo library to the executable
target_link_libraries (take_two_project TakeTwo)

# Install the executable locally
install(TARGETS take_two_project DESTINATION bin)
```

And your `thirdparty/CMakeLists.txt` file only needs the line:

```cmake
add_subdirectory (take_two)
```

Now we will add the TakeTwo project repository as a submodule for our new project.

```bash
cd thirdparty
# Add TakeTwo as a submodule
git submodule add https://github.com/<your_github_username>/take_two.git take_two
```

This will clone your TakeTwo project repository into the `thirdparty` folder, and register it as a submodule in a newly-created `.gitmodules` file.

Note: the TakeTwoProject repo will **not** track the TakeTwo submodule's files, but instead tracks a pointer to a single commit in the submodule repository. By default, this commit is the most recent commit on the submodule's master branch. In order to have the pointer track future commits to the master branch, you can add the flag `git submodule add -b master <repo_url> <local_folder>`.  You can also choose to track a different branch using the same flag: `git submodule add -b <branch_name> ...`

In my example case here, my submodule is pointing to a branch named `submodule` in this same repository, which is identical to the contents of the `v1-cmake-intro` folder.

Now we can compose a simple main function that utilizes the TakeTwo library. For example, my `src/take_two_project.cpp` file looks like this:

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
