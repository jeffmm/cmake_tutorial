# disable complaints about undocumented functions (assumes all are documented)
set(DOXYGEN_EXTRACT_ALL YES)
# enable support for standard library functions (e.g. std::vector)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

# Add sources for documentation (can use a GLOB here for multiple headers)
doxygen_add_docs(docs
    take_two/take_two.hpp
    "${CMAKE_CURRENT_SOURCE_DIR}/main.md"
    WORKING_DIRECTORY
    "${PROJECT_SOURCE_DIR}/include")
