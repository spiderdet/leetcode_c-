//
// Created by 47219 on 2022/7/11.
//

#ifndef LEETCODE_912_SORT_H
#define LEETCODE_912_SORT_H
#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include "utils/show_anything.h"
namespace lc912 {
    using namespace std;
    vector<int> temp;
    void merge(vector<int> &nums, int left, int mid, int right) {
        for (int i = left; i <= mid; i++) {
            temp[i] = nums[i];
        }
        cout << "left, mid, right: " << left << " " << mid << " " << right << endl;
        int l = left, r = mid + 1;
        for (int p = left; p <= right; p++) {
            if (l == mid + 1) break;
            if (r == right + 1) {
                nums[p] = temp[l++];
                continue;
            }
            if (temp[l] <= nums[r]) {
                nums[p] = temp[l++];
            } else {
                nums[p] = nums[r++];
            }
        }
        show_anything_h::show_vector(nums,left,right);
    }

    void mergeSort(vector<int> &nums, int left, int right) {
        if (right <= left) return;
        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);
        merge(nums, left, mid, right);
    }

    int partition(vector<int> &nums, int left, int right) {
        //可加入随机模块
        int l = left + 1, r = right;
        while (l <= r) {
            while (l <= r && nums[l] <= nums[left]) {
                l++;
            }
            while (l <= r && nums[r] >= nums[left]) {
                r--;
            }
            if (l > r) {
                break;
            }
            int temp = nums[l];
            nums[l] = nums[r];
            nums[r] = temp;
            l++;
            r--;
        }
        //if (r<0) return left;不需要！ 因为r最小是left,此时l=left+1，在3,4,4,4时出现
        int temp = nums[r];
        nums[r] = nums[left];
        nums[left] = temp;
        return r;
    }
    void fastSort(vector<int> &nums, int left, int right) {
        if (right - left <= 0) return;
        int pivot = partition(nums, left, right);
        fastSort(nums, left, pivot - 1);
        fastSort(nums, pivot + 1, right);
    }
    void fast_sort_optimized(vector<int>& nums, int left, int right) {
        if (right <= left) return;
        //randomize
        random_device rd;
        default_random_engine eng(rd());
        int l, r, pivot,temp,temp2;
        while(right > left){ //通过这种方式减少一次递归函数栈的使用！模仿STL的sort函数，还可以加上
            uniform_int_distribution<int> dis(left,right); //随机数左右都是闭区间
            temp2 = dis(eng);
            temp = nums[temp2];
            nums[temp2] = nums[left];
            nums[left] = temp;
            l = left + 1, r = right, pivot = nums[left];
            while (true) {
                while (l <= r && nums[l] <= pivot) ++l;
                while (l <= r && nums[r] >= pivot) --r;
                if (l > r) break;
                temp = nums[l];
                nums[l] = nums[r];
                nums[r] = temp;
                ++l;
                --r;
            }
            temp = nums[r];//记住r是pivot点！
            nums[r] = pivot;
            nums[left] = temp;
            fast_sort_optimized(nums,left,r-1);
            left = r+1;
        }
    }
    vector<int> sortArray(vector<int> &nums) {
        // fastSort(nums,0,nums.size()-1);
        temp = nums;
        mergeSort(nums, 0, nums.size() - 1);
        return nums;
    }

    void test(){
        vector<int> v1 = {5,2,3,1}, v2={5,1,1,2,0,0};
        show_anything_h::show_vector(v1);
        sortArray(v1);
        show_anything_h::show_vector(v1);
        show_anything_h::show_vector(v2);
        sortArray(v2);
        show_anything_h::show_vector(v2);
    }
}// end of namespace
#endif //LEETCODE_912_SORT_H
