//
// Created by 47219 on 2022/8/5.
//

#ifndef LEETCODE_BINARY_SEARCH_H
#define LEETCODE_BINARY_SEARCH_H
#include <vector>
#include <iostream>
using namespace std;
namespace binary_search {
    int left_bound(vector<int> nums, int target) {
        int left = 0, right = nums.size() - 1;
        // 搜索区间为 [left, right] 闭区间！
        while (left <= right) { //可以用<=
            int mid = left + (right - left) / 2; //这种写法防止left+right 对于int越界
            if (nums[mid] < target) {
                // 搜索区间变为 [mid+1, right]
                left = mid + 1;
            } else if (nums[mid] > target) {
                // 搜索区间变为 [left, mid-1]
                right = mid - 1;
            } else if (nums[mid] == target) {
                // 收缩右侧边界 放心大胆的mid-1，就算这次mid是最后的左边界，最后left=right的时候
                //=这次的mid-1，因为这次的mid是左边界，所以还会left=mid+1一次，就又回来了！
                right = mid - 1;
            }
        }
        //总情况：1.ssstttgg, 2.sssss, 3sssst,4ssstt,5tttt,6ttgg,7tggg,8gggg.
        //134情况在跳出循环前left=right=result-1,进入left=mid+1分支，left=result,right=result-1
        //2情况最后left=right=length-1，进入left=mid+1分支，left=length,right=length-1
        //5678情况，在跳出循环前left=right=0所以进入right=mid-1分支，left=0,right=-1
        //因此总结，return left才最方便,额外检查left越界即可,
        //可不可以检查right越界，但return left? 不可以！检查right越界不能处理情况2！！
        // 检查越界情况，小心越界！
//        if (left >= nums.size() || nums[left] != target)
//            return -1;
//        return left;
        if(right+1 > nums.size() || nums[right+1] != target)
            return -1;
        return right+1;
    }
    void test(){
        vector<int> a = {3,3,3,3,3};
        cout << left_bound(a,2);
    }
}
#endif //LEETCODE_BINARY_SEARCH_H
