cmake_minimum_required(VERSION 3.22)
project(leetcode)

set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps=obj")
#set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -save-temps=obj")


add_executable(leetcode main.cpp utils/utils.h  utils/sort.h utils/show_anything.h
         utils/myMath.h utils/input_helper.h  utils/myAlgorithm.h )