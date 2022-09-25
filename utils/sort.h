#ifndef MAIN_CPP_SORT_H
#define MAIN_CPP_SORT_H
#include <vector>
#include <random>
#include <iostream>
#include "show_anything.h"
using namespace std;
namespace sort_h{
    template<typename T>
    int partition(vector<T> &nums, int left, int right) {
        //函数返回left和right之间的一个整数k，代表分割成[left,k-1],k,[k+1,right]三个部分，分别<=,=,>=k
        //注意最后返回的是r！可以分两种情况，最后是在第一个while l>r的还是第二个while l>r的，发现都是r最后和left换
        //如果是3,4,4,4,4这样的，最后r=left，l=left+1注意r不会越界！
        random_device rd;
//        default_random_engine gen(1);//保证每次运行都相同
        default_random_engine gen(rd());//用机器码保证真随机
        uniform_int_distribution<int> dis(left,right);
        int rand = dis(gen);
        T tp = nums[left];
        nums[left] = nums[rand];
        nums[rand] = tp;
        int l = left + 1, r = right;
        while (true) {
            while (l <= r && nums[l] <= nums[left]) {  // 如果此时l==r，关键来了，如果这个数nums[l]比pivot小，就会在这个
                //循环进去，从而l指向下一个数，而r指向最后一个比pivot小的数，因此最后return r。而如果这个数nums[l]比pivot大，
                //就会跳过这循环，进入下一个循环r--，那r指向的仍然是比pivot小的最后一个数，综上都应该return r
                ++l;
            }
            while (l <= r && nums[r] >= nums[left]) {
                --r;
            }
            if (l > r) break;
            int temp = nums[l];
            nums[l] = nums[r];
            nums[r] = temp;
            ++l;
            --r;
        }
        int temp = nums[r];
        nums[r] = nums[left];
        nums[left] = temp;
        return r;
    }
    template <typename T>
    void fastSort(vector<T> &nums, int left, int right) {
        if (right - left <= 0) { //因为是闭区间！所以是<=0，不是<=1!
            return;
        }
        int pivot = partition(nums, left, right);
        cout << "pivot index: " << pivot << ", nums[pivot]: " << nums[pivot] << endl;
        cout << "show vector now"<<endl;
        show_anything_h::show_vector(nums);
        fastSort(nums, left, pivot - 1);
        fastSort(nums, pivot + 1, right);
    }
    void test(){
        vector<int> nums={4,1,7,2,5,6,3};
        random_device rd;
        default_random_engine gen(rd());
        uniform_int_distribution<int> dis(1,20);
//    for(int & num : nums){
//        num = dis(gen);
//    }
        show_anything_h::show_vector(nums);
        sort_h::fastSort(nums,0,nums.size()-1);
        show_anything_h::show_vector(nums);
    }
}

#endif //MAIN_CPP_SORT_H
