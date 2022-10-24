cmake_minimum_required(VERSION 3.22)
project(leetcode)

set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps=obj")
#set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -save-temps=obj")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors") #用于取消复制消除功能，这个语句的意思是替换！

#add "" to wrap spaces in file name, other wise "407 trapping" will be regarded as file 407 and file trapping
add_executable(leetcode main.cpp utils/utils.h  utils/sort.h utils/show_anything.h
         utils/myMath.h utils/input_helper.h  utils/myAlgorithm.h
        )