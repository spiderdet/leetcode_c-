#ifndef MAIN_CPP_2426_NUMBER_OF_PAIRS_SATISFYING_INEQUALITY_H
#define MAIN_CPP_2426_NUMBER_OF_PAIRS_SATISFYING_INEQUALITY_H
#include <iostream>
#include <vector>
#include <set>
#include "utils/Binary Indexed Tree.h"
using namespace std;
namespace lc2426_h{

    //用归并排序的框架，详见语雀：算法-归并排序
    long long merge_count(vector<int>& v,vector<int>& aux, int left, int right, int diff){
        if(left >= right) return 0;
        if(left == right - 1){
            long long result = 0, temp;
            if(v[left]<=v[right]+diff) result=1;
            if(v[left]>v[right]){
                temp = v[left];
                v[left] = v[right];
                v[right] = temp;
            }
            return result;
        }
        int middle = left+(right-left)/2;
        long long result =0;
        result = merge_count(v,aux,left, middle,diff);
        result += merge_count(v,aux, middle+1, right,diff);
        int p1 = middle, p2 = right, p3;
        while(p1 >= left && p2 > middle){
            if(v[p1]<=v[p2]+diff) p2--;
            else{
                result+=right-p2;
                p1--;
            }
        }
        if(p2 == middle){
            result+= (long long)(p1-left+1)*(right-middle);
        }
        p1 = middle, p2 = right, p3 = right;
        while(p1 >= left && p2 > middle){
            if(v[p1]>v[p2]) aux[p3--] = v[p1--];
            else aux[p3--] = v[p2--];
        }
        if(p2==middle){
            while(p1>=left) aux[p3--] = v[p1--];
        }
        else{
            while(p2>middle) aux[p3--] = v[p2--];
        }
        //copy aux to v
        for(int i = left; i <= right; ++i){
            v[i]=aux[i];
        }
        return result;
    }
    long long num_of_pairs_merge(vector<int>& nums1, vector<int>& nums2, int diff) {
        int n = nums1.size();
        vector<int> aux;
        for(int i = 0; i <n;++i){
            nums1[i] -= nums2[i];
        }
        aux.resize(n);
        return merge_count(nums1,aux,0,n-1,diff);
    }


    class comp_j{
    public:
        bool operator()(const int&a ,const int&b){return a>=b;}
    };
    class comp_i{
    public:
        bool operator()(const int&a, const int&b){return a>b;}
    };
//#define DEBUG_num_of_pairs_BIT
//详见语雀-算法题归并排序-离散树状数组
    long long num_of_pairs_BIT(vector<int>& nums1, vector<int>& nums2, int diff){
        //BIT里从后往前遍历，详见语雀
        using namespace BIT_h;
        int n = nums1.size();
        long long answer = 0;
        set<int,greater<int>> aux;
        //因为是nums[i] <= nums[j] + diff 即到i的时候，要找已经遍历过的j,那就是nums[j]>=nums[i]-diff，所以是降序排列
        //并且重载lower_bound的comp为>=
        vector<int> sorted_unduplicated_vec;
        for(int i = 0; i <n;++i){
            nums1[i] -= nums2[i];
            aux.insert(nums1[i]);
        }
        for(auto c : aux){
            sorted_unduplicated_vec.push_back(c);
        }
#ifdef DEBUG_num_of_pairs_BIT
        cout << "sorted_unduplicated_vec : "<< endl;
        for(auto c : aux){cout << c << ' ';}
        cout << endl;
#endif
        int unduplicated_n = sorted_unduplicated_vec.size();
        BIT<int> bit(unduplicated_n);
        for(int i = n-1;i>=0;i--){
            //为了找有几个j满足nums[j]>=nums[i]+diff
            int j_idx = lower_bound(sorted_unduplicated_vec.begin(), sorted_unduplicated_vec.end(),
                                    nums1[i]-diff, comp_j()) - sorted_unduplicated_vec.begin();
            answer += bit.query(j_idx-1);
            //为了更新i对应的位置
            int i_idx = lower_bound(sorted_unduplicated_vec.begin(), sorted_unduplicated_vec.end(),
                                    nums1[i], comp_i()) - sorted_unduplicated_vec.begin();
            bit.increment(i_idx,1);
#ifdef DEBUG_num_of_pairs_BIT
            cout << "i = " << i <<", nums1[i]= " << nums1[i] << ", i_idx = " << i_idx << ", j_idx = "<<j_idx
            << endl;
            cout << "answer = " << answer << endl;
#endif
        }
        return answer;
    }
    void test_lc2426(){
        vector<int> v1={3,2,5}, v2 = {2,2,1}, v3={3,-1},v4={-2,2};
        int diff1 = 1, diff2 = -1;
//        cout << num_of_pairs_merge(v1, v2, diff1) << " " << num_of_pairs_merge(v3, v4, diff2) << " ";
//        cout << endl;
        cout << num_of_pairs_BIT(v1, v2, diff1) << endl << num_of_pairs_BIT(v3, v4, diff2) << endl;
        cout << endl;
    }
}
#endif //MAIN_CPP_2426_NUMBER_OF_PAIRS_SATISFYING_INEQUALITY_H
