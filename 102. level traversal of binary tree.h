#ifndef LEETCODE_102_LEVEL_TRAVERSAL_OF_BINARY_TREE_H
#define LEETCODE_102_LEVEL_TRAVERSAL_OF_BINARY_TREE_H
#include <iostream>
#include <vector>
#include <memory>
#include "utils/utils.h"
namespace lc102 {
    using namespace std;
    using namespace utils;

    vector<vector<int>> result;
    void dfs(const shared_ptr<TreeNode>& root, int level){
        if(!root) return;
        if(result.size()<level+1){
            result.emplace_back(vector<int>{root->val});
        }
        else{
            result[level].push_back(root->val);
        }
        dfs(root->left, level+1);
        dfs(root->right, level+1);
    }
    vector<vector<int>>& levelOrder(shared_ptr<TreeNode>& root) {
        dfs(root,0);
        return result;
    }
    void test() {
        vector<int> inputs = {3, 9, 20, INT32_MIN, INT32_MIN, 15, 7};
        shared_ptr<TreeNode> root = r_build_tree(inputs, 0);
        vector<vector<int>> temp = levelOrder(root);
        show_graph(temp);
    }

}
#endif //LEETCODE_102_LEVEL_TRAVERSAL_OF_BINARY_TREE_H
