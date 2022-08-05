//
// Created by 47219 on 2022/7/11.
//

#ifndef LEETCODE_UTILS_H
#define LEETCODE_UTILS_H
#include <iostream>
#include <utility>
#include <vector>
#include <string>
namespace utils {
    using namespace std;
    struct TreeNode {
        int val;
        shared_ptr<TreeNode> left;
        shared_ptr<TreeNode> right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, shared_ptr<TreeNode> left, shared_ptr<TreeNode> right) : val(x), left(std::move(left)), right(std::move(right)) {}
    };
    shared_ptr<TreeNode> r_build_tree(vector<int>& inputs, int index){
        //用int数组建立二叉树，用INT32_MIN作为空节点。
        if(index>= inputs.size() || inputs[index]==INT32_MIN) return nullptr;
        shared_ptr<TreeNode> root(new TreeNode(inputs[index], r_build_tree(inputs,index*2+1),
                                               r_build_tree(inputs,index*2+2)));
        return root;
    }

//    TreeNode* build_tree(vector<int>& inputs, int index){
//        if(inputs.empty()) {cout << " empty inputs! " << endl; return nullptr;}
//        int max_index = inputs.size()-1;
//        shared_ptr<TreeNode> root(new TreeNode(inputs[0]));
//        queue<shared_ptr<TreeNode>> q;
//        q.push(root);
//        while(!q.empty()){
//
//        }
//    }
    template<typename T>
    void show_vector(vector<T> &nums, int left_idx=0, int right_idx=-1,string message="") {//[left_idx,right_idx]
        int size = nums.size(); //一定要用int存下来！要不然nums.size是unsigned int ,与-1比较大小会反过来！
        if(nums.size()==0){
            cout << "empty vector" <<endl;
            return;
        }
        if(right_idx==-1) right_idx=size-1;
        if(right_idx>=size){
            cout << "right_idx out of range, right_idx:"<<right_idx<<", nums_size:"<<size<<". note that right_idx is also closed [,]" << endl;
            return;
        }
        cout << message<<endl;
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
#endif //LEETCODE_UTILS_H
