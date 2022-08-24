//
// Created by 47219 on 2022/8/19.
//

#ifndef LEETCODE_MS3_1_H
#define LEETCODE_MS3_1_H
#include <vector>
#include <string>
using namespace std;
int solution(vector<int> &X, vector<int> &Y, int W) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    set<int> s;
    for(auto x : X){
        s.insert(x);
    }
    int start = INT32_MIN, count = 0;
    for(auto ele:s){
        if(ele>start+W){
            start = ele;
            ++count;
        }
    }
    return count;
}
string solution(string &S) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    map<int,int,greater<>> M;
    for(char s :S){
        ++M[s-'0'];
    }
    string left, right, temp_str;
    int temp_num;
    char char_temp;
    for(auto & m : M){
        if(m.second>=2){
            if(m.first != 0 || (m.first == 0 && !left.empty())){
                temp_num = m.second/2;
                temp_str = "";
                m.second = m.second & 1;
                char_temp = '0'+m.first;
                left.append(temp_num,char_temp);
                right = temp_str.append(temp_num, char_temp)+right;
            }
        }
    }
    for(auto m :M){
        if(m.second >= 1){
            char char_temp = '0'+m.first;
            left.append(1,char_temp);
            break;
        }
    }
    return left + right;
}
pair<int,int> r_calculate_citizens_fuels(const vector<vector<int>>& graph, int prev, int curr){
    if(graph[curr].size()==1 && graph[curr][0]==prev) return pair<int,int>(1,1);
    int citizens = 1, fuels = 0;
    pair<int,int> temp;
    for(int i : graph[curr]){
        if(i != prev){
            temp = r_calculate_citizens_fuels(graph, curr, i);
            citizens+=temp.first;
            fuels+=temp.second;
        }
    }
    int total_fuels = fuels+(citizens-1)/5+1;
    return (curr==0) ? pair<int,int>(citizens,fuels):pair<int,int>(citizens,total_fuels);
}

int solution(vector<int> &A, vector<int> &B) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    int n = A.size();
    if(n == 0) return 0;
    vector<vector<int>> graph(n+1);
    for (int i = 0; i < n; ++i) {
        graph[A[i]].push_back(B[i]);
        graph[B[i]].push_back(A[i]);
    }
    return r_calculate_citizens_fuels(graph,-1,0).second;
}
#endif //LEETCODE_MS3_1_H
