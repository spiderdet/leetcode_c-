//
// Created by 47219 on 2022/8/13.
//

#ifndef LEETCODE_MEITUAN_1_H
#define LEETCODE_MEITUAN_1_H
#include <map>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
using namespace std;

int test(){
    int n, count =0;
    cin >> n;
    if(n<=2){
        cout << 0;
        return 0;
    }
    vector<int> v(n);
    unordered_map<int,int> m;
    unordered_map<int,int> map_k;
    unordered_map<int,int> map_i;
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        map_k[v[i]]++;
    }
    map_k[v[0]]--;
    for (int j = 1; j < n-1; ++j) {
//        m.clear();
        map_k[v[j]]--;
        map_i[v[j-1]]++;
        for(auto c :map_i){
            count += c.second * map_k[3*v[j]-c.first];
        }
    }
    cout << count;
    return 0;
}

#endif //LEETCODE_MEITUAN_1_H
