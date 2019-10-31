# Take Two v0.1

## Make the local git repo

```bash
mkdir take_two
cd take_two
# Initialize the folder as a git repository
git init
# Create a README file
echo "# Take Two" >> README.md
# Add the README file and make your first commit
git add README.md
git commit -m "First commit"
```

Now create an empty repository on GitHub named take_two. Then push your local repository to the remote GitHub repository

```bash
# Add remote github repo to track local repo
git remote add origin https://github.com/<your_username>/take_two
# Verify the remote url
git remote -v
# Push the commit
git push -u origin master
```

## Organize the directory structure

Create folders and files like so

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

The files `include/take_two/take_two.hpp` and `src/take_two.cpp` will be the header and source files for the Take Two library. In my example, the library has a single class `TakeTwo`, which wraps a static member function that takes two values and computes some basic arithmetic (boring, I know, but it's instructive).

The `.gitignore` file should have the line

```bash
/build*
```

and the top-level `CMakeLists.txt` file should be

```cmake
# Tested for CMake version 3.XX
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

and the file `src/CMakeLists.txt` should be

```cmake
# Define library headers
set (HEADERS ../include/take_two/take_two.hpp)

# Make a static library (tradeoff of memory for better performance)
add_library (take_two STATIC take_two.cpp ${HEADERS})

# Set target includes
target_include_directories (take_two PUBLIC ../include)

# Make install targets
install (TARGETS take_two DESTINATION lib)
install (FILES ${HEADERS} DESTINATION include/take_two)
```

Then add and push the changes to the remote

```bash
git add -A
git commit -m "Built directory structure"
git push origin master
```

To build the library, do the following

```bash
mkdir build
cd build
cmake ..
make
```

The library `libtake_two.a` will be built inside the `src` folder in the new `build` directory. To install the library on a local machine, you could copy `include/take_two` into your `/usr/local/include` and copy `libtake_two.a` into your `/usr/local/lib`.

Our install targets handle this automatically. Simply do

```bash
make install
```

And you can start using the library right away using the usual linking:

```bash
g++ myproject.cpp -ltake_two
```

You could also include Take Two as a subproject in the parent project's build tree by including Take Two as a submodule. More on that later.
