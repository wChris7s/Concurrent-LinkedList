cmake_minimum_required(VERSION 3.24)
project(Concurrent_LinkedList)

set(CMAKE_CXX_STANDARD 23)

add_executable(Concurrent_LinkedList src/concurrent_linked_list.h src/main.cpp src/random_data.h)
