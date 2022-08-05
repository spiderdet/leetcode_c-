//
// Created by 47219 on 2022/7/11.
//

#ifndef LEETCODE_315_COUNT_LESS_THAN_CURR_H
#define LEETCODE_315_COUNT_LESS_THAN_CURR_H
#include <iostream>
#include <vector>
#include <tuple>
#include "utils.h"
namespace lc315 {
    using namespace std;
    vector<tuple<int,int>> temp_nums;
    void merge(vector<tuple<int, int>> &tuple_nums, vector<int> &counts, int left, int mid, int right);

    void merge_sort(vector<tuple<int, int>> &tuple_nums, vector<int> &counts, int left, int right);

    vector<int> countSmaller(vector<int> &nums) {
        vector<int> counts(nums.size(), 0);
        // tuple<int,int> idx_val;
        vector<tuple<int, int>> tuple_nums;
        for (int i = 0; i < nums.size(); i++) {
            tuple_nums.emplace_back(i, nums[i]);
        }
        temp_nums=tuple_nums;
        merge_sort(tuple_nums, counts, 0, nums.size() - 1);
        return counts;
    }

    void merge_sort(vector<tuple<int, int>> &tuple_nums, vector<int> &counts, int left, int right) {
        if (right == left) return;
        int mid = left + (right - left) / 2;
        merge_sort(tuple_nums, counts, left, mid);
        merge_sort(tuple_nums, counts, mid + 1, right);
        merge(tuple_nums, counts, left, mid, right);
    }

    void merge(vector<tuple<int,int>>& tuple_nums, vector<int>& counts,int left, int mid, int right){
        for (int i = left; i <= mid; i++) {
            temp_nums[i] = tuple_nums[i];
        }
        int l = left, r = mid+1;
        for (int p = left; p <= right; p++) {
            if (l == mid + 1) break;
            if (r == right + 1) {
                counts[get<0>(temp_nums[l])]+=r-mid-1;
                tuple_nums[p] = temp_nums[l++];
                continue;
            }
            if (get<1>(temp_nums[l]) <= get<1>(tuple_nums[r])) {
                counts[get<0>(temp_nums[l])]+=r-mid-1;
                tuple_nums[p] = temp_nums[l++];
            } else {
                tuple_nums[p] = tuple_nums[r++];
            }
        }
    }
    void test(){
        vector<int> v1 = {5,2,6,1};
        utils::show_vector(v1);
        vector<int> counts = countSmaller(v1);
        utils::show_vector(counts);

    }
}// end of namespace
#endif //LEETCODE_315_COUNT_LESS_THAN_CURR_H
