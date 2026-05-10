cmake_minimum_required(VERSION 4.2)
set(NAME polynomial)
project(${NAME})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

#set(SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(CUSTOM "${NAME}")
set(TESTS   "test_${NAME}")
set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories("${INCLUDE}" gtest)

add_subdirectory(include)
#add_subdirectory(src)
add_subdirectory(samples)
add_subdirectory(gtest)
add_subdirectory(test)