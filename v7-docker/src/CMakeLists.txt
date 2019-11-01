# Represent all files that end with .cpp with the SOURCES variable
file (GLOB SOURCES "*.cpp")

find_package (TakeTwo REQUIRED)

# Compile sources into an executable binary
add_executable (take_two_project ${SOURCES})

# Link the TakeTwo library to the executable
target_link_libraries (take_two_project TakeTwo::TakeTwo)

# Install the executable locally
install (TARGETS take_two_project DESTINATION bin)
