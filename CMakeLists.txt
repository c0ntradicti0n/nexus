cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(io_util
  io_util.cpp
)
add_library(moves
  moves.cpp
)

# Add the necessary source files or libraries for the undefined symbols
# Replace "source_file1.cpp" and "source_file2.cpp" with the actual files
add_library(surge
  surge/src/position.cpp
  surge/src/tables.cpp
  surge/src/types.cpp
)


include_directories(${CMAKE_SOURCE_DIR}/plog)
link_directories(${CMAKE_SOURCE_DIR}/plog)
include_directories(${CMAKE_SOURCE_DIR}/.)
link_directories(${CMAKE_SOURCE_DIR}/.)

set(FOO_SRCS "main.cpp")

enable_testing()

add_executable(hello_test
  tests/hello_test.cc
)
add_executable(prog
  main.cpp
)

# Link necessary libraries to the hello_test target
target_link_libraries(hello_test
  PRIVATE
    GTest::gtest_main
    io_util  # Add any other required libraries here
    moves
    surge
)

target_link_libraries(prog
  PRIVATE
    io_util
    moves
    surge
)

include(GoogleTest)
gtest_discover_tests(hello_test)
