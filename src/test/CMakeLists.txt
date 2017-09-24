
add_executable(test_match test_match.cpp)
target_link_libraries(test_match gtest_main pcrlib)
# ${htslib_static} ${zlib_static} pthread

add_test(NAME test_match COMMAND test_match)
