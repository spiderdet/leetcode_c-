//
// Created by 47219 on 2022/8/6.
//

#ifndef LEETCODE_MS_TEST2_H
#define LEETCODE_MS_TEST2_H
#include <iostream>
#include <vector>
#include <map>
#include "../utils/utils.h"
namespace MS_TEST2 {
    using namespace std;

    int MOD = 1000000007;

    template<typename T, typename T2>
    T gcd(T x, T2 y) {
        if (y == 0) return x;
        else return gcd(y, x % y);
    }

    struct classcomp {
        bool operator()(const pair<int, int> &l, const pair<int, int> &r) const {
            return l.first / double(l.second) < r.first / double(r.second);
        }
    };

    int try_add(pair<long long, long long> sum, pair<int, int> x, int k) {
        long long gcd_number = gcd(sum.second, x.second);
        long long sum_multi = x.second / gcd_number, x_multi = sum.second / gcd_number, den = sum.second * sum_multi;
        for (; k >= 0; k--) {
            if (den < sum.first * sum_multi + k * x.first * x_multi) continue;
            else break;
        }
        return k;
    }

    bool add(pair<long long, long long> &sum, pair<int, int> x, int k) {
        if(k==0) return false;
        long long gcd_number = gcd(sum.second, x.second);
        long long sum_multi = x.second / gcd_number, x_multi = sum.second / gcd_number, den = sum.second * sum_multi;
        sum.second = den;
        sum.first = sum.first * sum_multi + k * x.first * x_multi;
        long long gcd2 = gcd(sum.first,sum.second);
        sum.first/=gcd2;
        sum.second/=gcd2;
        return sum.second == sum.first;
    }
    void subtract(pair<long long, long long> &sum, pair<int,int>x, int k){
        if(k==0) return;
        long long gcd_number = gcd(sum.second, x.second);
        long long sum_multi = x.second / gcd_number, x_multi = sum.second / gcd_number, den = sum.second * sum_multi;
        sum.second = den;
        sum.first = sum.first * sum_multi - k * x.first * x_multi;
        long long gcd2 = gcd(sum.first,sum.second);
        sum.first/=gcd2;
        sum.second/=gcd2;
        return;
    }


    void backtrack(map<pair<int, int>, int, classcomp> &complements,
                   map<pair<int,int>,int>::reverse_iterator it,
                   int &count, pair<long long, long long> &sum, long long prefix) {
        if (it == complements.rend()) return;
        int k = try_add(sum, it->first, it->second);

        for (int j = k; j >= 0; j--) {
            //加入j个，sum增加，判断sum=1的话count++，sum减少，continue， sum<1的话回溯++it，回溯结束sum减少
            if (add(sum, it->first, j)) {
                cout << "curr:(" << it->first.first <<"," << it->first.second << "),max_k:"<<it->second<<",k:"<< k <<", j:"<< j
                     << ", sum:(" << sum.first << "," << sum.second<<"), count :" <<count << endl;
                count = (count + prefix*utils::Combination_single_time(j, it->second)) % MOD;
            } else {
                cout << "curr:(" << it->first.first <<"," << it->first.second << "),max_k:"<<it->second<<",k:"<< k <<", j:"<< j
                << ", sum:(" << sum.first << "," << sum.second<<"), count :" <<count << endl;
                backtrack(complements, ++it, count, sum,prefix*utils::Combination_single_time(j,it->second));
                --it;
                //backtrack没有取消进入的影响
            }
            subtract(sum,it->first, j);
        }
    }

    int solution(vector<int> &X, vector<int> &Y) {
        // write your code in _C++ (_C++14 (g++ 6.2.0))
        map<pair<int, int>, int, classcomp> complements;
        int n = X.size(), gcd_number, count = 0;
        if (n <= 0) return 0;
        for (int i = 0; i < n; ++i) {
            if (X[i] > Y[i]) continue;
            else if (X[i] == Y[i]) {
                count++;
                continue;
            }
            gcd_number = gcd(X[i], Y[i]);
            pair<int, int> temp(X[i] / gcd_number, Y[i] / gcd_number);
            complements[temp]++;
        }
        pair<long long, long long> sum(0,1);
        auto it = complements.rbegin();
        backtrack(complements, it, count, sum, 1);
        return count;
    }

    void test() {
        vector<int> X = {1,2,3,2,12,8,3,6};
        vector<int> Y = {5,10,15,5,15,10,5,10};
//        vector<int> X = {1,2,12,8,3};
//        vector<int> Y = {5,10,15,10,5};
        cout << solution(X,Y);

    }
}
#endif //LEETCODE_MS_TEST2_H
