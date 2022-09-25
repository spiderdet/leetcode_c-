//
// Created by 47219 on 2022/8/29.
//

#ifndef LEETCODE_ALI_2_H
#define LEETCODE_ALI_2_H
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
#define FILE_CIN //从文件输入，不需要时注释掉

void dfs(vector<vector<pair<int,int>>>& board, int& count, const vector<pair<int,int>>& dirs, int last, int i, int j, int n, int m){
    //保证不越界
    int curr_value = board[i][j].first;
    if(curr_value == -1) return;
    if(last != -1 && last != curr_value){
        return ;
    }
    ++count;
    last = curr_value;
    board[i][j].first = -1;//别忘了修改board
    for(auto dir:dirs){
        int new_i = i + dir.first, new_j = j + dir.second;
        if(new_i < n && new_j < m){
            dfs(board,count,dirs,last,new_i, new_j,n,m);
        }
    }
    //不用恢复对board的破坏，防止重复数块
}

int test_ali_2(){
#ifdef FILE_CIN
    //方法1 重定向输入流，注意clion的执行目录在cmake-build-debug下
    freopen("./test_inputs/ali_2.in","r",stdin);
//    freopen("out.txt","w",stdout);//重定向输出
    //方法2
//    ifstream infile("./test_inputs/ali_2.in");
//    if(!infile.is_open()){
//        cout << "file is not open" << endl;
//        return -1;
//    }
//    streambuf* cinbuf = cin.rdbuf();
//    cin.rdbuf(infile.rdbuf())
#endif
    int n, m, k, temp;
    cin >> n >> m >> k;
    vector<vector<pair<int,int>>> board(n, vector<pair<int,int>>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> temp; // cin >> value, value is score for each cell
            board[i][j] = move(pair<int,int>(temp,i*n+j));
        }
    }
    vector<pair<int,int>> dirs = {pair<int,int>{1,0},pair<int,int>{0,1},pair<int,int>{0,-1}};
    //注意一定是三个方向！ 防止010,111的情况出现。
    map<int , vector<int>, greater<>> value_cells_map;
    vector<int> results;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int count = 0, curr_value = board[i][j].first;
            if(curr_value == -1) continue; //在递归里保证，但为了防止map被污染还是加上
            dfs(board, count, dirs, -1, i, j, n, m);
            cout<< "curr_value " << curr_value << ", count: " << count << endl;
            value_cells_map[curr_value].push_back(count);
            results.push_back(curr_value*count);
            make_heap(results.begin(), results.end());
        }
    }
    for(int i = 0 ; i< k; ++i){
        pop_heap(results.begin(),results.end());
        cout << results.back() << " ";
        results.pop_back();
    }

}

#endif //LEETCODE_ALI_2_H
