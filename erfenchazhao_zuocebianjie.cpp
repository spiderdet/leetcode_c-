#include <iostream>
#include <vector>
#include <random>
namespace erfenchazhao_zuocebianjie {
    using namespace std;

    int searchLeft(vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid - 1;
            } else left = mid + 1;
        }
        if (left >= nums.size() || nums[left] != target) {
            return -1;
        } else return left;
    }

}