cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

ADD_LIBRARY(io_util
        io_util.cpp
        )
ADD_LIBRARY(moves
        moves.cpp
        )

include_directories(${CMAKE_SOURCE_DIR}/plog)
link_directories(${CMAKE_SOURCE_DIR}/plog)
include_directories(${CMAKE_SOURCE_DIR}/.)
link_directories(${CMAKE_SOURCE_DIR}/.)

set(FOO_SRCS "main.cpp")

enable_testing()

add_executable(
  hello_test
        tests/hello_test.cc
)
add_executable(
        prog
        main.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)
target_link_libraries(
        prog
        io_util

)
target_link_libraries(
        prog
        moves

)


include(GoogleTest)
gtest_discover_tests(hello_test)
