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

