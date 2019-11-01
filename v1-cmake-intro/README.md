# TakeTwo v0.1

This tutorial is meant to help developers who are new to CMake get started by building a C++ library. I will provide step-by-step instructions on building a simple library called TakeTwo. There are more advanced tutorials out there, but my goal is to start from a minimalist foundation, and gradually build up to a project that has unit tests, continuous integration, containerization, etc.

Let's get started.

## Make the git repo

We first initialize an empty git repository locally, for a project named take_two

```bash
mkdir take_two
cd take_two
# Initialize the folder as a git repository
git init
# Create a README file
echo "# TakeTwo" >> README.md
# Add the README file and make your first commit
git add README.md
git commit -m "First commit"
```

Now create an empty repository on GitHub with the name take_two. Push your local repository to the remote GitHub repository using the commands

```bash
# Have remote GitHub repo track our local git repo
git remote add origin https://github.com/<your_username>/take_two
# Push the commit to the remote
git push -u origin master
```

## Organize the directory structure

A CMake library is typically organized in the following way:

```bash
take_two
├── include
│   └── take_two
│       └── take_two.hpp
├── src
│   ├── CMakeLists.txt
│   └── take_two.cpp
├── README.md
├── CMakeLists.txt
└── .gitignore
```

The files `include/take_two/take_two.hpp` and `src/take_two.cpp` will be the header and source files for the TakeTwo library. In my example project, the library has a single class `TakeTwo`, which wraps a static member function that takes two values and computes some basic arithmetic (boring, I know, but it's instructive).

and the top-level `CMakeLists.txt` file should always start with the `cmake_minimum_required()` function, followed by the `project()` details.

```cmake
# Tested for CMake version 3.4+
cmake_minimum_required(VERSION 3.4)

# Project name and a few useful settings. Other commands can pick up the results
project(TakeTwo
    VERSION 0.1
    DESCRIPTION "An example project with CMake"
    LANGUAGES CXX
)

# The compiled library code is here
add_subdirectory(src)
```

This `CMakeLists.txt` file will tell CMake to now search the `src` directory for additional CMake files. The file `src/CMakeLists.txt` will give CMake the instructions on how to build the library.

```cmake
# Define library headers
set (HEADERS ../include/take_two/take_two.hpp)

# Make a static library (tradeoff of memory for better performance)
add_library (TakeTwo STATIC take_two.cpp ${HEADERS})

# Set target includes
target_include_directories (TakeTwo PUBLIC ../include)

# Make install targets
install (TARGETS TakeTwo DESTINATION lib)
install (FILES ${HEADERS} DESTINATION include/take_two)
```

This is a minimalist CMake file, but it will get the job done. To see a more robust version, check out the `src/CMakeLists.txt` file in the `v3-examples` directory.

The `.gitignore` file should have the line:

```bash
/build*
```

as well as any additional files you do **not** want to be tracked in your git repo. Never track your built binaries or libraries using git.

Add and commit your changes locally, then push the changes to your remote repo on GitHub.

```bash
git add -A
git commit -m "Built directory structure"
git push origin master
```

To build the library using CMake, do the following

```bash
mkdir build
cd build
cmake ..
make
```

The library `libTakeTwo.a` will be built inside the `src` folder in the new `build` directory. To install the library on a local machine, you could copy `include/take_two` into your `/usr/local/include` and copy `libTakeTwo.a` into your `/usr/local/lib`.

Our install make target handles this automatically. Simply do

```bash
make install
```

and you can start using the library right away using the usual linking:

```bash
g++ myproject.cpp -lTakeTwo
```

You could also include TakeTwo as a subproject in the parent project's build tree by adding it as a submodule. We'll discuss how to do that next.
