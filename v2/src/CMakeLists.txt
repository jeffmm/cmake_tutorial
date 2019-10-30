# Find all headers in the project include folder
file(GLOB HEADERS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/take_two/*.hpp")

# Make a static library (tradeoff of memory for better performance)
add_library(take_two STATIC take_two.cpp ${HEADERS})

# Add an alias so the target can be used while building
add_library(take_two::take_two ALIAS take_two)

# Set the include directory for builds (tests, examples, etc) and for clients
target_include_directories(take_two PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

# Associate the include files with the target, so they will be installed
set_target_properties(take_two PROPERTIES PUBLIC_HEADER "${HEADERS}")

# Set install targets and destinations
install(TARGETS take_two
    EXPORT take_two-targets
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/take_two)

# Export additional install files (for clients using CMake)
install(EXPORT take_two-targets
    NAMESPACE take_two::
    FILE take_two-config.cmake
    DESTINATION lib/cmake/take_two)

