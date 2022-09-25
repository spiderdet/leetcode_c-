#ifndef MAIN_CPP_SHOW_ANYTHING_H
#define MAIN_CPP_SHOW_ANYTHING_H
#include <iostream>
#include <vector>
using namespace std;
namespace show_anything_h{
    template<typename T>
    void show_vector(vector<T> &nums, string pre_message="", int left_idx=0, int right_idx=-1) {//[left_idx,right_idx]
        int size = nums.size(); //一定要用int存下来！要不然nums.size是unsigned int ,与-1比较大小会反过来！
        if(!pre_message.empty()) cout << pre_message << " ";
        if(size==0){
            cout << "empty vector(size==0)"<< endl;
            return;
        }
        if(right_idx==-1) right_idx=size-1;
        if(right_idx>=size){
            cout << "right_idx out of range, right_idx:"<<right_idx<<", nums_size:"<<size<<". note that right_idx is also closed [,]" << endl;
            return;
        }
        for (int i = left_idx;i<=right_idx;i++) {
            cout << nums[i] << " ";
        }
        cout << endl;
    }
    template<typename T>
    void show_graph(vector<vector<T>> & graph){
        int n = graph.size();
        cout << "graph has " << n << " nodes\n";
        for (int i = 0; i <n;i++){
            cout << "node " << i << " has next nodes:";
            for (auto j : graph[i] ){
                cout << j << ", ";
            }
            cout << endl;
        }
    }
    template<typename T1,typename T2>
    void show_vecPair(vector<pair<T1,T2>> v){
        int n = v.size();
        cout << "This vector has " << n << " pairs\n";
        for (auto i : v){
            cout << i.first << " " << i.second << endl;
        }
    }

}
#endif //MAIN_CPP_SHOW_ANYTHING_H
