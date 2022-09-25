//
// Created by 47219 on 2022/8/25.
//

#ifndef LEETCODE_MS4_H
#define LEETCODE_MS4_H

int solution(int N) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    int base = 1, max_num=INT32_MIN, temp_num;
    if(N <0){
        N = -N;
        max_num = INT32_MAX;
        while(N/base != 0){
            if(N%(base*10)/base==5){
                temp_num = N%base + N/(base*10)*base;
                max_num = min(max_num, temp_num);
            }
            base *= 10;
        }
        max_num = -max_num;
    }
    else{
        max_num=INT32_MIN;
        while(N/base != 0){
            if(N%(base*10)/base==5){
                temp_num = N%base + N/(base*10)*base;
                max_num = max(max_num, temp_num);
            }
            base *= 10;
        }
    }
    return max_num;
}
//cout << solution(15958) << " " << solution(-5859) << " " << solution(-5000);


int solution(vector<int> &A) {
    int MAX_NUM = 1000000000;
    map<int,int> prefix_sum_map;
    int temp_prefix_sum = 0, count=0;
    long long temp;
    for(auto a : A){
        temp_prefix_sum += a;
        prefix_sum_map[temp_prefix_sum]++;
    }
    for(auto prefix_sum : prefix_sum_map){
        if(prefix_sum.second == 1) continue;
        temp = static_cast<long long>(prefix_sum.second) * static_cast<long long>(prefix_sum.second-1)/2;
        if(temp > MAX_NUM || temp+count > MAX_NUM){
            return -1;
        }
        else count += temp;
        if(prefix_sum.first == 0){
            count += prefix_sum.second;
            if(count > MAX_NUM) return -1;
        }
    }
    return count;
}
vector<int> A(100000,0);
vector<int> B(5,0);
vector<int> C = {2,-2,3,0,4,-7};
cout << solution(A);

int solution(vector<int> &A) {
    int n = A.size();
    if(n<=2) return 0;
    const int MAX_NUM = 1000000000;
    map<int,int,greater<>> interval_map; //key is interval length, value is number of intervals
    int gap = A[1] - A[0], interval_length = 2,result = 0, curr_gap;
    long long temp;
    for(int i = 2; i < n; ++i){
        curr_gap = A[i]-A[i-1];
        if(curr_gap == gap){
            ++interval_length;
        }
        else{
            if(interval_length >= 3){
                interval_map[interval_length]++;
            }
            interval_length = 2;
            gap = curr_gap;
        }
    }
    if(interval_length >= 3){
        interval_map[interval_length]++;
    }
    for(auto interval : interval_map) {
        temp = static_cast<long long>(interval.first - 2) *
               static_cast<long long>(interval.first - 1) / 2;
        if (temp > MAX_NUM || temp * interval.second > MAX_NUM ||
            result + temp * interval.second > MAX_NUM) return -1;
        else result += temp * interval.second;
    }

    return result;
}
vector<int> A = {-1,1,3,3,3,2,3,2,1,0};
vector<int > B(10000,2);
vector<int > C(100000,2);
cout << solution(B) << ' ' << solution(A) << " " << solution(C);
#endif //LEETCODE_MS4_H
