# Get all files that end with .cpp
file (GLOB SOURCES "*.cpp")

# Compile sources into executable binary
add_executable (take_two_project ${SOURCES})

# Link the take_two library
target_link_libraries (take_two_project take_two)

# Install the executable locally
install(TARGETS take_two_project DESTINATION bin)
