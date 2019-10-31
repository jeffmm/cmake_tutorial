# Define library headers
set (HEADERS ../include/take_two/take_two.hpp)

# Make a static library (tradeoff of memory for better performance)
add_library (TakeTwo STATIC take_two.cpp ${HEADERS})

# Set target includes
target_include_directories (TakeTwo PUBLIC ../include)

# Make install targets
install (TARGETS TakeTwo DESTINATION lib)
install (FILES ${HEADERS} DESTINATION include/take_two)
