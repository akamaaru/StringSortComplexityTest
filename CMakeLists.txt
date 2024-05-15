cmake_minimum_required(VERSION 3.25)
project(string_sort)

set(CMAKE_CXX_STANDARD 17)

add_executable(string_sort main.cpp quick_sort.cpp utils.cpp merge_sort.cpp utils.h quick_sort.h merge_sort.h radix_counting_sort.h radix_counting_sort.cpp radix_quick_sort.h radix_quick_sort.cpp)
