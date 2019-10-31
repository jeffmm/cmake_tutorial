# Define library headers
set (HEADERS ../include/take_two/take_two.hpp)

# Make a static library (tradeoff of memory for better performance)
add_library (take_two STATIC take_two.cpp ${HEADERS})

# Set target includes
target_include_directories (take_two PUBLIC ../include)

# Make install targets
install (TARGETS take_two DESTINATION lib)
install (FILES ${HEADERS} DESTINATION include/take_two)
