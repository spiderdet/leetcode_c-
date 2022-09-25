cmake_minimum_required(VERSION 3.22)
project(leetcode)

set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps=obj")
#set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -save-temps=obj")

#erfenchazhao_zuocebianjie.cpp "25 reverse_kgroup.h" fast_sort.cpp
# "215 k_largest.h" "315 count_less_than_curr.h" "912 sort.h" utils_h.h "210 course prerequisites 2.h" "102. level traversal of binary tree.h" binary_search.h MS_test2.h test.h meituan_1.h
#MS3-1.h  Alibaba_1.h MS4.h class_test.h multithread_test.h exams/ali_2.h exams/ali_3.h exams/huawei_2.h exams/huawei_3.h
#multi-thread/coutABCiteratively.hmulti-thread/child_main_print_iteratively.h
#"84. largest_rectangle_in_histogram.h"
add_executable(leetcode main.cpp utils/utils.h  utils/sort.h utils/show_anything.h
        calculator.h)