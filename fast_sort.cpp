//
// Created by 47219 on 2022/7/7.
//
#include <iostream>
#include <vector>
#include <random>
namespace fast_sort {
    using namespace std;

    void show_vector(vector<int> &nums);

    int partition(vector<int> &nums, int left, int right) {
        //函数返回left和right之间的一个整数k，代表分割成[left,k-1],k,[k+1,right]三个部分，分别<=,=,>=k
        //注意最后返回的是r！可以分两种情况，最后是在第一个while l>r的还是第二个while l>r的，发现都是r最后和left换
        //如果是3,4,4,4,4这样的，最后r=left，l=left+1注意r不会越界！
//    random_device rd;
//    default_random_engine gen = default_random_engine(1);
//    uniform_int_distribution<int> dis(left,right);
//    int rand = dis(gen);
//    int tp = nums[left];
//    nums[left] = nums[rand];
//    nums[rand] = tp;
        int l = left + 1, r = right;
        while (true) {
            while (l <= r && nums[l] <= nums[left]) {
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

    void fastSort(vector<int> &nums, int left, int right) {
        if (right - left <= 0) { //因为是闭区间！所以是<=0，不是<=1!
            return;
        }
        int pivot = partition(nums, left, right);
        cout << pivot << " " << nums[pivot] << endl;
        show_vector(nums);
        fastSort(nums, left, pivot - 1);
        fastSort(nums, pivot + 1, right);
    }

    void show_vector(vector<int> &nums) {
        for (int num: nums) {
            cout << num << " ";
        }
        cout << endl;
    }
    void test(){
        vector<int> nums={3,4,4,4,4};
        random_device rd;
        default_random_engine gen = default_random_engine(rd());
        uniform_int_distribution<int> dis(1,20);
//    for(int & num : nums){
//        num = dis(gen);
//    }
        show_vector(nums);
        fastSort(nums,0,nums.size()-1);
        show_vector(nums);
    }

}
//int main(){
//    fast_sort::test();
//    return 0;
//}