cmake_minimum_required(VERSION 3.25)
project(unit_tests)

set(CMAKE_CXX_STANDARD 17)

add_library(complex_lab INTERFACE)
target_include_directories(complex_lab INTERFACE scr)

include_directories(scr)

add_subdirectory(scr)
add_subdirectory(tst)
add_subdirectory(lib/googletest)

set_target_properties(unit_tests PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(unit_tests_lib PROPERTIES LINKER_LANGUAGE CXX)