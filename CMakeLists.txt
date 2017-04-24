cmake_minimum_required(VERSION 3.7)
project(transactions)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -ggdb3")

set(SOURCE_FILES main.cpp)
add_executable(transactions ${SOURCE_FILES})