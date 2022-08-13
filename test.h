//
// Created by 47219 on 2022/8/13.
//

#ifndef LEETCODE_TEST_H
#define LEETCODE_TEST_H

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int main(){
    int n, count =0;
    cin >> n;
    if(n<=2){
        cout << 0;
        return 0;
    }
    vector<int> v(n);
    unordered_map<int,int> m;
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    for (int j = 1; j < n-1; ++j) {
        m.clear();
        for (int i = 0; i < j; ++i) {
            m[3*v[j]-v[i]]++;
        }
        for(int k = j+1;k<n;++k){
            count+=m[v[k]];
        }
    }
    cout << count;
    return 0;
}
#endif //LEETCODE_TEST_H
