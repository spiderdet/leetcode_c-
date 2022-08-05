//
// Created by 47219 on 2022/7/11.
//

#ifndef LEETCODE_215_K_LARGEST_H
#define LEETCODE_215_K_LARGEST_H
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
namespace lc215{
using namespace std;
int max_k;
void r_findkLargest(vector<int>& nums, int left, int right, int k);
int findKthLargest(vector<int>& nums, int k) {
    //这是方法1，用双指针类似快速排序的思路来递归地做
//    r_findkLargest(nums,0,nums.size()-1,k);
//    return max_k;
    //下面方法2，直接用STL库的堆或者优先级队列
//    priority_queue<int,vector<int>,greater<>> q;
//    for(auto c :nums){
//        q.push(c);
//        if(q.size()>k){
//            q.pop();
//        }
//    }
//    return q.top();
    //下面方法3，用make_heap
    make_heap(nums.begin(),nums.end());
    for (int i =0; i< k-1;i++){
        pop_heap(nums.begin(),nums.end());
        nums.pop_back();
    }
    return nums[0];

}
void r_findkLargest(vector<int>& nums, int left, int right, int k){
    //平凡情况
    if(right==left){
        max_k = nums[right];
        return;
    }
    //随机一项放在left处，之后在[left+1,right]上寻找
    random_device rd;
    default_random_engine gen = default_random_engine(rd());
    uniform_int_distribution<int> dis(left, right);
    int rand = dis(gen);
    int tp = nums[rand];
    nums[rand] = nums[left];
    nums[left] = tp;
    // 让l,r双指针相遇来找到这项的位置
    cout << "nums[left]: " << nums[left] << endl;
    int l = left+1, r = right;
    while(true){
        while(l<=r&&nums[l]<=nums[left]) l++;
        while(l<=r&&nums[r]>=nums[left]) r--;
        if(l>r) break;
        int temp = nums[l];
        nums[l] = nums[r];
        nums[r] =temp;
        l++;
        r--;
    }
    int temp = nums[left];
    nums[left] = nums[r];
    nums[r] = temp;
    cout << "left,right,r:" << left << right << r << endl;
    //根据r的位置与k的关系，来返回或递归调用。
    if(right-r+1==k){
        max_k = nums[r];
        return;
    }
    else if(right-r+1>k){
        r_findkLargest(nums,r+1,right,k);
    }
    else r_findkLargest(nums,left,r-1,k-right+r-1);
}
void test(){
    vector<int> v = {3,2,1,5,6,4};
    for (auto c: v) {
        cout << c << " ";
    }
    cout << endl;
    int k = 2;
    int result = findKthLargest(v,k);
    cout << "result:" << result;
}
}// end of namespace lc215
#endif //LEETCODE_215_K_LARGEST_H
