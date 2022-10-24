#ifndef MAIN_CPP_1049_LAST_STONE_WEIGHT_II_H
#define MAIN_CPP_1049_LAST_STONE_WEIGHT_II_H
#include <iostream>
#include <vector>
#include <numeric> //accumulate()
#include <memory> //shared_ptr
using namespace std;
namespace lc1049{
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        typedef pair<int,int> value_last; //first: current max value, second: stone index+1 that update this dp value
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int half_sum = sum/2;
        unique_ptr<value_last[]> dp = make_unique<value_last[]>(half_sum+ 1); // dp[0]=0是需要的，否则无法实现dp[2]=max(dp[2],dp[2-2]+2)
        //fill dp array
        for(int i = 0 ; i <n;++i){ //将二维dp：dp[i][j]压缩成了一维dp[j]
            for(int j = half_sum;j>0;--j){
                if(j>=stones[i] && dp[j-stones[i]].first+stones[i] > dp[j].first){
                    dp[j].first = dp[j-stones[i]].first+stones[i];
//                    dp[j].second = j-stones[i];//这样是back数组，记录的是dp[j]是由前面哪个dp更新的
                    dp[j].second = i+1;//这样不仅能找到是由前面哪个dp更新的，而且可以记录是哪个物体更新的这次dp[j]，但为了防止没有被物体更新的时候也是0引起混淆，这里的i应该要+1！
                }
            }
        }
        //展示dp数组和back数组。
//        for(int i =1;i <= half_sum; i++){
//            cout << i << ' ' <<  dp[i].first << ' ' << dp[i].second-1 << ' ';
//            if(dp[i].second > 0) cout << stones[dp[i].second-1]<< endl;
//            else cout << " No " << endl;
//        }
        //显示抵消路径
        vector<int> one_pile_idx, another_pile_idx;
        int cur_weights = half_sum, temp_stone_idx;
        while((temp_stone_idx = dp[cur_weights].second) ){ // back index not zero
             one_pile_idx.push_back(temp_stone_idx-1);
             cur_weights = cur_weights - stones[temp_stone_idx-1];
        }
        auto one_pile_it = one_pile_idx.begin();//one_pile_idx里面是从大到小的idx！所以it不用reverse就已经是从大到小
        for(int i =n-1;i>=0;--i){
            if(one_pile_it == one_pile_idx.end()) another_pile_idx.push_back(i);
            else if(i>*one_pile_it) another_pile_idx.push_back(i);
            else one_pile_it++;
        }
        show_anything_h::show_vector(one_pile_idx,"one_pile_idx :");
        show_anything_h::show_vector(another_pile_idx,"another_pile_idx :");
        //要就再显示抵消路径就是归并两个有序链表了。不赘述
        //return answer
        return sum - 2*dp[half_sum].first;
    }
    void test(){
        vector<int> v1 = {2,7,4,1,8,1}, v2 = {31,26,33,21,40};
        cout << lastStoneWeightII(v1) << endl << lastStoneWeightII(v2);
    }
}
#endif //MAIN_CPP_1049_LAST_STONE_WEIGHT_II_H
