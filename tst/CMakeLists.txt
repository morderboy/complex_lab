set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})  # Correct the variable name here

add_executable(${BINARY} ${SOURCES})  # Use SOURCES here

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)