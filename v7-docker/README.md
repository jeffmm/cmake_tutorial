# TakeTwoProject v0.2

We are going to build the TakeTwoProject again, this time using Docker.

We can ship our library pre-compiled on a [Docker](https://www.docker.com/) image alongside our CMake repo. What Docker lets us do is ship an operating system with the library already installed in an image that clients can run as a container.

## Update CMake install script

Before we start using Docker, let's update our `src/CMakeLists.txt` inside the TakeTwo library project so that we can more easily install our library using CMake:

```cmake
# Find all headers in the project include folder
file(GLOB HEADERS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/take_two/*.hpp")

# Make a static library (tradeoff of memory for better performance)
add_library(TakeTwo STATIC take_two.cpp ${HEADERS})

# Add an alias so the target can be used while building
add_library(TakeTwo::TakeTwo ALIAS TakeTwo)

# Set the include directory for builds (tests, examples, etc) and for clients
target_include_directories(TakeTwo PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

# Associate the include files with the target, so they will be installed
set_target_properties(TakeTwo PROPERTIES PUBLIC_HEADER "${HEADERS}")

# Set install targets and destinations
install(TARGETS TakeTwo
    EXPORT TakeTwoTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/take_two)

# Export additional install files (for clients using CMake)
install(EXPORT TakeTwoTargets
    NAMESPACE TakeTwo::
    FILE TakeTwoConfig.cmake
    DESTINATION lib/cmake/TakeTwo)
```

The exported targets will now install a file called `TakeTwoConfig.cmake` that will let future users of your library link to it using the `find_package(TakeTwo)` function in CMake if the library is installed locally.

Note that external projects will need to invoke your library as `TakeTwo::TakeTwo` in the `target_link_libraries()` function in CMake. The namespace separated from the library name by double colons is a naming convention to prevent collisions inside large projects that may use similarly-named libraries. This is why we linked to the Catch2 library using the designation `Catch2::Catch2`.

## Distribute your library with Docker

Inside a `docker` folder, we will create a `Dockerfile` and a few helper scripts:

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
├── docker
│   ├── docker_install.sh
│   ├── install.sh
│   └── Dockerfile
├── README.md
├── CMakeLists.txt
├── .travis.yml
└── .gitignore
```

The `Dockerfile` will have instructions on how to build the OS.

```bash
# The Docker image we are using as a base image. This is a 
# pre-configured OS; in this case, it is using a light-weight
# version of linux called Alpine with gcc/g++ installed.
FROM frolvlad/alpine-gxx

# Create a directory on the image and have all following
# commands be run from within that directory.
WORKDIR /build

# Install necessary packages and libraries to download and
# install our library.
RUN apk update && apk upgrade && apk add git cmake make

# Clone the repository and install the library as usual
RUN git clone --recursive https://github.com/<your_github_username>/take_two.git . &&\
    mkdir build &&\
    cd build &&\
    cmake -DTESTS=TRUE .. &&\
    make && make test && make install

# Remove any unnecessary packages and delete build files
RUN rm -rf /build && apk del git

# Set working directory to a folder called app
WORKDIR /app
```

At each `RUN` command, the subsequent commands are run from within the `/build` working directory on the Docker image, as though we are rebooting the OS and running our first command. The final `WORKDIR` command ensures that future commands to the image will be run within that folder.

In order to build the Docker image, from the same folder as the `Dockerfile`, run

```bash
docker build -t <your_username>/take_two .
```

This builds a docker image locally by running all the commands listed in `Dockerfile` on top of the base image next to `FROM`. This includes downloading our git repository and installing the library. The image is named `<your_username>/take_two`, and is automatically assigned a `latest` tag to let users of your image know that it's the most up-to-date version. You can see your image using the command `docker images`. 

In order to interact with the commandline within our container, we use the command

```bash
docker run --rm -it -v ${PWD}:/app <your_username>/take_two sh
```

The `docker run` command will use the image to build a container on your computer. The `--rm` flag lets Docker know that it's okay to close the container when you exit out of the container. The `-it` flags make the session "interactive." The `-v ${PWD}:/app` flag mounts your current working directory onto the container in the folder `/app`. The final command `sh` tells the container to run the Bourne shell after startup.

Notice that if you create a new file within the container, it will appear in your current working directory on your local computer. This is because the `-v` flag causes your machine and the container to share your local directory.

Notice also that if you create a file anywhere other than `/app` on the image, it will not be there if you exit the container and create a new one. A newly-created Docker container is a clone of the Docker image, and changing the container does not affect the image. When a container disappears, so do its contents (not including any mounted directories).

You can run commands inside the container without having to shell into it. To do that, run

```bash
docker run --rm -v ${PWD}:/app <your_username>/take_two <command>
```

While the command runs, you can see the container using the command `docker ps`. The `--rm` flag will close the container after the command has finished, however.

For the command, we can provide a script called `docker/install.sh` that installs and runs our TakeTwoProject using CMake. 

```bash
#!/bin/sh
# Put your project installation script here, e.g.:
mkdir build
cd build
cmake ..
make
make install
# Run project after installation
take_two_project
```

Make sure you make this script executable using the command `chmod +x docker/install.sh`. We may as well add a script called `docker/docker_install.sh` that users can put in their top-level directory that will run the install script inside the Docker container

```bash
#!/bin/bash
# This should be run from one level above the install.sh script
docker run --rm -v ${PWD}:/app <your_username>/take_two ./docker/install.sh
```

Now we have provided a `Dockerfile` that lets our users build a Docker image with our library already installed on it, along with some helper scripts for building and running their project inside the image.

If you wanted, you could also create an account on [Docker Hub](https://hub.docker.com/) and upload your image there. It's kind of like a repository for Docker images. You upload it using the command

```bash
docker push <your_dockerhub_username>/take_two
```

Now you see that the username you've been providing for your Docker image name should be the same as your Docker Hub username. If that's not the case, you should rename the image to fit your new username.

Your image will now automatically be downloaded by users who run a Docker command invoking your image name, or it can be downloaded explicitly using the command `docker pull <your_username>/take_two`.

## Use Docker to build a project with our library as a dependency

Let's see what it's like to use the Docker image we created for a project that uses TakeTwo as a dependency. The project folder should look something like this:

```bash
take_two_project
├── src
│   ├── CMakeLists.txt
│   └── take_two.cpp
├── docker
│   ├── install.sh
│   └── Dockerfile
├── docker_install.sh
├── README.md
├── CMakeLists.txt
└── .gitignore
```

The `.sh` scripts will be identical to the ones you've prepared in the TakeTwo project. The top-level `CMakeLists.txt` should no longer add any subdirectories except for `src`:

```cmake
cmake_minimum_required(VERSION 3.4)
project(TakeTwoProject
    VERSION 0.1
    DESCRIPTION "A project that uses TakeTwo as a submodule"
    LANGUAGES CXX
)

add_subdirectory(src)
```

The `src/CMakeLists.txt` file has changed a bit from last time as well:

```cmake
# Represent all files that end with .cpp with the SOURCES variable
file (GLOB SOURCES "*.cpp")

# Locate the TakeTwo library
find_package (TakeTwo REQUIRED)

# Compile sources into an executable binary
add_executable (take_two_project ${SOURCES})

# Link the TakeTwo library to the executable
target_link_libraries (take_two_project TakeTwo::TakeTwo)

# Install the executable locally
install (TARGETS take_two_project DESTINATION bin)
```

Now we are using the `find_package(TakeTwo)` function in CMake to locate the TakeTwo library. If the library did not exist, it would throw an error. We are also linking the library using the TakeTwo namespace, by convention.

We should now be able to run the `docker_install.sh` script. This will run our Docker container with our project folder mounted inside at `/app`, and then run the `install.sh` script. If all goes well, this will build, install, and run the project binary.

Practically speaking, if you were going to build a binary that you would run often, you should build another Docker image that had the binary pre-installed. This would be what you could put in the file `docker/Dockerfile`

```bash
FROM <your_username>/take_two

WORKDIR /build
RUN apk add git
RUN git clone https://github.com/<your_github_username>/take_two_project.git . &&\
    mkdir build &&\
    cd build &&\
    cmake .. &&\
    make &&\
    make install

RUN rm -rf /build && apk del git
WORKDIR /app
ENTRYPOINT ["take_two_project"]
```

In my example repository, my `docker/Dockerfile` is the one you used to build the image `<your_username>/take_two`.

In `Dockerfile` for the TakeTwoProject, the `ENTRYPOINT` command makes the default container behavior execute your take_two_project binary. Building this container from within the `docker` folder using

```bash
docker build -t <your_username>/take_two_project .
```

and running it anywhere on your machine with

```bash
docker run --rm <your_username>/take_two_project
```

would run the take_two_project binary by default. Like before, you can mount your local repository using the `-v ${PWD}:/app` flags, in case your program needs to produce any output or needs access to local files.

That's it! If you wanted to go the extra mile, you could set up Travis CI to test building the Docker image, or run your library unit tests on the Docker image. Either way, users of your library now only need Docker installed to immediately use your code in a platform-independent environment.
