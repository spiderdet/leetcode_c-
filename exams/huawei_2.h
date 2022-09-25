//
// Created by 47219 on 2022/9/7.
//

#ifndef LEETCODE_HUAWEI_2_H
#define LEETCODE_HUAWEI_2_H
#include <iostream>
#include <vector>
using namespace std;
#define FILE_CIN //从文件输入，不需要时注释掉
int min_time = INT32_MAX;
vector<int> dx = {0,0,1,-1};
vector<int> dy = {1,-1,0,0};
int M, N;
void dfs(vector<vector<char>>& board, int x, int y, int last_dir, int steps){
    cout << "x = " << x << ", y = " << y << ", board:" << board[x][y] << ",steps: " << steps <<endl;
    if(board[x][y] == 'E'){
        min_time = min(min_time, steps);
        cout << "min_time: " << min_time << ", at "<< x << ", " << y << endl;
        return ;
    }
    int new_x, new_y, curr_step;
    board[x][y] = 'X';
    for(int i =0; i<4;++i){
        new_x = x+dx[i];
        new_y = y+dy[i];
        if(new_x<0 || new_x >= M || new_y<0 || new_y >= N || board[new_x][new_y]=='X') continue;
        cout << "here is i = " << i << endl;
        curr_step = (i == last_dir) ? 1 : 2;
        dfs(board, new_x, new_y, i, steps+curr_step);
    }
    board[x][y] = 'B';
}
int huawei_2()
{
#ifdef FILE_CIN
    freopen("./test_inputs/huawei_2.in","r",stdin);
#endif
    // please define the C++ input here. For example: int a,b; cin>>a>>b;;
    cin >> M >> N;
    vector<vector<char>> board(M,vector<char>(N));
    pair<int, int> start, end;
    for(int i = 0; i<M;++i){
        string line;
        cin >> line;
        for(int j = 0; j < N ;++j){
            board[i][j] = line[j];
            if(line[j] == 'S'){
                start = pair<int,int>(i,j);
                cout <<"start: " << start.first << " " << start.second << endl;
            }
            if(line[j] == 'E'){
                end = pair<int,int>(i,j);
                cout <<"end: " << end.first << " " << end.second << endl;
            }
        }
    }
    // please finish the function body here.
    dfs(board, start.first, start.second, -1, 0);
    // please define the C++ output here. For example:cout<<____<<endl;
    if(min_time == INT32_MAX) cout << -1;
    else cout << min_time - 1;
    return 0;
}
#endif //LEETCODE_HUAWEI_2_H
