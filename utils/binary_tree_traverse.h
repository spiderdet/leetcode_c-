#ifndef MAIN_CPP_BINARY_TREE_TRAVERSE_H
#define MAIN_CPP_BINARY_TREE_TRAVERSE_H
#include <vector>
#include <iostream>
#include <stack>
#include "TreeNode.h"
using namespace std;
using namespace TreeNode_h;
namespace binary_tree_traverse_h{
    void preorder_traverse_r(const shared_ptr<TreeNode>& root){
        if(root == nullptr) return;
        cout << root->val << " ";
        preorder_traverse_r(root->left);
        preorder_traverse_r(root->right);
    }
    void preorder_traverse_nonr(const shared_ptr<TreeNode>& root){
        if(root == nullptr) return;//初始的root不能为空
        stack<shared_ptr<TreeNode>> s;
        s.push(root); //root的处理放到后面一起
        while(!s.empty()){   //两个while循环，外循环负责从stack取数，内循环负责输出“根“”左“，然后把”右“放到栈里，
            // 直到到最左下，再退出进入下一个外循环。
            shared_ptr<TreeNode> temp = s.top();
            s.pop();
            while(temp!=nullptr){
                cout << temp->val << " ";
                if(temp->right != nullptr) s.push(temp->right);
                temp = temp->left;
            }
        }
    }
    void midorder_traverse_r(const shared_ptr<TreeNode>& root){
        if(root == nullptr) return;
        midorder_traverse_r(root->left);
        cout << root->val << " ";
        midorder_traverse_r(root->right);
    }
    void midorder_traverse_nonr(shared_ptr<TreeNode> root){
        stack<shared_ptr<TreeNode>> s;
//        while(root!=nullptr){   //这个可以和下面的合并！
//            s.push(root);
//            root = root->left;
//        }
//        while(!s.empty()){
//            root = s.top();
//            s.pop();
//            cout << root->val << " ";
//            root = root->right;
//            while(root!=nullptr){
//                s.push(root);
//                root = root->left;
//            }
//        }
        //合并后如下：
        while(root || !s.empty()){
            while(root!=nullptr){
                s.push(root);
                root = root->left;
            }//此时结束时，保证一定在最左下点。接下来可以出栈了
            root = s.top();
            s.pop();
            cout << root->val << " ";
            root = root->right;
        }
    }
    void postorder_traverse_r(const shared_ptr<TreeNode>& root){
        if(root == nullptr) return;
        postorder_traverse_r(root->left);
        postorder_traverse_r(root->right);
        cout << root->val << " ";
    }
    void postorder_traverse_nonr(shared_ptr<TreeNode> root){
        stack<pair<shared_ptr<TreeNode>,bool>> s;//因为一个节点要出栈两次，第一次出栈是为了右子节点，第二次出栈是输出自己
        //所以用bool=false表示没出过栈，将是第一次出栈，出过栈后（其实不pop)把bool设为true，下一次遇到就知道是将要第二次出栈了
        while(root!=nullptr){  //无法合并，因为下面的while循环要分类。
            s.emplace(root,false);
            root = root->left;
        }
        while(!s.empty()){
            root = s.top().first;
            if(s.top().second){
                cout << root->val << ' ';
                s.pop();
                continue;
            }
            else{
                s.top().second = true;
                root = root->right;
                while(root!=nullptr){
                    s.emplace(root,false);
                    root = root->left;
                }
            }
        }
    }
    void test(){
        int null = INT32_MIN;
        vector<int> v = {1,2,3,4,5,6,7};
        shared_ptr<TreeNode> root(move(r_build_tree(v,0)));
        show_Tree(root);
        postorder_traverse_r(root);
        cout << endl;
        postorder_traverse_nonr(root);
        cout << endl;
    }
}
#endif //MAIN_CPP_BINARY_TREE_TRAVERSE_H
