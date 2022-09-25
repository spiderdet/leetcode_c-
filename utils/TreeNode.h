#ifndef MAIN_CPP_TREENODE_H
#define MAIN_CPP_TREENODE_H
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <string>
namespace TreeNode_h{
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
    void show_Tree(const shared_ptr<TreeNode>& root){
        queue<shared_ptr<TreeNode>> q;
        q.emplace(root);
        while(!q.empty()){
            int n = q.size();
            for(int i =0; i<n;++i){
                shared_ptr<TreeNode> temp = q.front();
                q.pop();
                if(temp == nullptr) {cout << "# "; continue;}
                else{
                    cout << temp->val << " ";
                    q.push(temp->left);
                    q.push(temp->right);
                }
            }
            cout << endl;
        }
    }
}
#endif //MAIN_CPP_TREENODE_H
