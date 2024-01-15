set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

add_executable(${BINARY} ${SOURCES} "complex_lab.cpp")

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} "complex_lab.cpp")