# Take Two


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

Now create a remote repository on GitHub named take_two

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

The `.gitignore` file should have

```bash
/build*
```

and the `CMakeLists.txt` in the take_two directory should be

```bash
# Tested for CMake version 3.X
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

and the `src` folder `CMakeLists.txt` should be

```bash
file(GLOB HEADERS CONFIGURE_DEPENDS "${TakeTwo_SOURCE_DIR}/include/take_two/*.hpp")

# Make a static or dynamic depending on user setting
add_library(take_two take_two.cpp ${HEADERS})

# We need this directory, and users of our library will need it too
target_include_directories(take_two PUBLIC ../include)
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
