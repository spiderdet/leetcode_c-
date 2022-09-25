#ifndef MAIN_CPP_84_LARGEST_RECTANGLE_IN_HISTOGRAM_H
#define MAIN_CPP_84_LARGEST_RECTANGLE_IN_HISTOGRAM_H
#include <iostream>
#include <vector>
#include "utils/show_anything.h"
namespace lc84{
    using  namespace  std;
    int find_largest_area(vector<int> &v){
        vector<pair<int,int>> stack;
        //定义为严格单调递增的栈，定义是(左边界，高度)，计算面积只在1. pop元素时计算 2.最后结束时，对栈中残余元素计算。
        int max_area = 0, n = v.size(), last_left_border;
        for(int i= 0; i<n;++i){
            pair<int,int> temp_pair = {i,v[i]};
            if(stack.empty()) stack.push_back(move(temp_pair)); //如果为空直接加入
            last_left_border = i; //在每个for循环里重新赋值，防止while循环没进的情况下在while结束后对temp_pair的边界进行更新
            while(!stack.empty() && stack.back().second > v[i]){ //用stack.back()之前一定要注意是否为空！
                max_area = max(max_area, (temp_pair.first - stack.back().first) * stack.back().second);
                last_left_border=stack.back().first;
                stack.pop_back();
            }
            temp_pair.first = last_left_border;
            if(!stack.empty() && stack.back().second == v[i]){//跳过相等的，因为1.不用算面积 2. 不用更新左边界，啥都不用做
                continue;
            }
            stack.push_back(move(temp_pair));//此时stack已经pop完比temp大的，尾元素一定比它小或为空，所以加进去。
        }
        for(auto c : stack){
            max_area = max(max_area,(n-c.first)*c.second); //在遍历完后再对单调栈内的元素算一遍面积，以末尾作为右边界。
        }
        return max_area;
    }
    void test(){
        vector<int> v1= {2,1,5,6,2,3};
        cout << find_largest_area(v1);
    }

}
#endif //MAIN_CPP_84_LARGEST_RECTANGLE_IN_HISTOGRAM_H
