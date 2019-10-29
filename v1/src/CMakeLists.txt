file(GLOB HEADERS CONFIGURE_DEPENDS "${TakeTwo_SOURCE_DIR}/include/take_two/*.hpp")

# Make a static or dynamic depending on user setting
add_library(take_two take_two.cpp ${HEADERS})

# We need this directory, and users of our library will need it too
target_include_directories(take_two PUBLIC ../include)
