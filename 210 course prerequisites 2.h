//
// Created by 47219 on 2022/7/27.
//

#ifndef LEETCODE_210_COURSE_PREREQUISITES_2_H
#define LEETCODE_210_COURSE_PREREQUISITES_2_H
#include <iostream>
#include <vector>
#include <tuple>
#include "utils/utils.h"
namespace lc210{
    using namespace std;
    vector<int> res;
    bool flag = true;
    void dfs(vector<vector<int>> &, vector<int>&, vector<bool>&, int);
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        flag = true;
        for(auto i : prerequisites){
            graph[i[0]].push_back(i[1]);
        }
//        utils::show_graph(graph);
        vector<bool> visited(numCourses);
        vector<int> path;
        for(int i = 0; i < numCourses; i++){
            if (visited[i]) continue;
            dfs(graph,path,visited,i);
            if(!flag){
                res.clear();
                return res;
            }
        }
//        std::reverse(res.begin(), res.end());
        return res;
    }
    void dfs(vector<vector<int>> &graph, vector<int>& path, vector<bool>& visited, int node){
         for(auto i : path){
             if(i==node) {
                 flag =false;
                 return;
             }
         }
         if(visited[node]) return;
         visited[node]=true;
         path.push_back(node);
         for(auto j:graph[node]){
            dfs(graph,path,visited,j);
            if(!flag) return;
         }
         path.pop_back();
         res.push_back(node);
    }
    void test(){
        vector<int> temp1= {1,0};
        vector<int> temp2= {2,0};
        vector<int> temp3= {3,1};
        vector<int> temp4= {3,2};
        vector<vector<int>> pre = {temp1,temp2,temp3,temp4};
        vector<int> result = findOrder(pre.size(), pre);
        utils::show_vector(result);
    }
}


#endif //LEETCODE_210_COURSE_PREREQUISITES_2_H
