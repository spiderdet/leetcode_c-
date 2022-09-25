//
// Created by 47219 on 2022/9/7.
//

#ifndef LEETCODE_HUAWEI_3_H
#define LEETCODE_HUAWEI_3_H
#include <iostream>
#include <vector>
using namespace std;
#define FILE_CIN //从文件输入，不需要时注释掉
vector<pair<int,int>> check_dirs = {{-1,0},{1,0}};
vector<pair<int,int>> move_dirs = {{-1,0},{0,-1},{0,1},{1,0}};
int min_steps = INT32_MAX;
vector<pair<int,int>> answer;
int M, N;
void dfs(vector<vector<int>>& board, pair<int,int> pos, vector<pair<int,int>>& visited, int steps){
    int check_x, check_y;
    pair<int, int> new_pos;
    visited.push_back(pos);
    board[pos.first][pos.second] = -1;
    for(int i = 0; i< 2 ;++i){
        check_x = pos.first+check_dirs[i].first;
        check_y = pos.second+check_dirs[i].second;
        if(check_x < 0 || check_x >= M || check_y <0 || check_y >= N) continue;
        if(board[check_x][check_y]== 1 && steps < min_steps){
            min_steps = steps;
            answer.clear();
            answer = visited;
            answer.emplace_back(check_x,check_y);
        }
    }
    for(int j = 0; j < 4; ++j){
        new_pos.first = pos.first+move_dirs[j].first;
        new_pos.second = pos.second+move_dirs[j].second;
        if(new_pos.first < 0 || new_pos.first >= M || new_pos.second <0 ||new_pos.second >= N ||
           board[new_pos.first][new_pos.second] == -1) continue;
        if(board[new_pos.first][new_pos.second] == 0) dfs(board, new_pos, visited, steps+1);
    }
    board[pos.first][pos.second] = 0;
}
int huawei_3()
{
#ifdef FILE_CIN
    freopen("./test_inputs/test.in","r",stdin);
#endif
    // please define the C++14 input here. For example: int a,b; cin>>a>>b;;
    int start_x, start_y;
    cin >> M >> N >> start_x >> start_y;
    --start_x;
    --start_y;
    vector<vector<int>> board(M, vector<int>(N));
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < N; ++j){
            cin >> board[i][j];
        }
    }
    vector<pair<int,int>> visited;
    // please finish the function body here.
    dfs(board,pair<int,int>(start_x,start_y), visited, 0);
    // please define the C++14 output here. For example:cout<<____<<endl;
    if(min_steps == INT32_MAX) cout << -1 << " " << -1;
    else{
        for(auto c : answer){
            cout << c.first+1 << " " << c.second+1 << " ";
        }
    }
    return 0;
}
#endif //LEETCODE_HUAWEI_3_H
