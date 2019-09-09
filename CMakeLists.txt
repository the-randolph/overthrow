cmake_minimum_required(VERSION 2.7.1)
project(overthrow)
set(CMAKE_CXX_FLAGS "-std=c++1z -Wall -Wextra -g -O0")
add_executable(overthrow player.cpp gameState.cpp main.cpp)

