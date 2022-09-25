//
// Created by 47219 on 2022/8/29.
//

#ifndef LEETCODE_ALI_3_H
#define LEETCODE_ALI_3_H
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
//#include <stdio.h>
using namespace std;

int get_tag(int num){
    int temp = 0;
    if(num % 337==0) temp +=1;
    if(num % 3==0) temp+=2;
    if((num & 1) == 0) temp+=4;
    return temp;
}
bool check_tag_overlap(int tag1, int tag2){
    if(tag1%2 == 0 && tag2%2==0) return false;
    if((tag1/2)%2 == 0 && (tag2/2) % 2 ==0) return false;
    if((tag1/4)%2 == 0 && (tag2/4) % 2 ==0) return false;
    return true;
}
int test_ali_3(){
//    freopen("ali_3.in","r",stdin);//重定向输入流//in.txt 建在程序所在的文件夹里
//    ifstream in("ali_3.in");
//    streambuf *cinbuf = cin.rdbuf();
//    cin.rdbuf(in.rdbuf());
    int n, m;
    n = 2;
    m = 3;
//    cin >> n;
//    cin >> m;
//    cout << n << m << endl;
//     vector<int> a(n), b(m);
    // 能整除2,3,337, 分别二进制的111， tag
    int temp;
    long long result = 0;
    vector<int> a = {2022, 337}, b = {1011, 2, 6};
    map<int, int> a_map, b_map;
    for(int i = 0; i< n; ++i){
        temp = a[i];
        temp = get_tag(temp);
        a_map[temp]++;
        cout << "i: " << i << ", " << temp << " " << a_map[temp] <<endl;
    }
    cout << endl;
    for(int i = 0; i< m; ++i){
        temp = b[i];
        temp = get_tag(temp);
        b_map[temp]++;
        cout <<  "i: " << i << ", " << temp << " " << b_map[temp] <<endl;
    }
    cout << endl;
    for(auto a_pair: a_map){
        for(auto b_pair: b_map){
//            if(check_tag_overlap(a_pair.first,b_pair.first)){
            if((a_pair.first|b_pair.first) == 7){
                result += a_pair.second*b_pair.second;
            }
        }
    }
    cout << result;
    return 0;
}
#endif //LEETCODE_ALI_3_H
