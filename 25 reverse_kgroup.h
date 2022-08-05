//
// Created by 47219 on 2022/7/9.
//

#ifndef LEETCODE_25_REVERSE_KGROUP_H
#define LEETCODE_25_REVERSE_KGROUP_H
#include <vector>
#include <memory>
namespace lc25{
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode* reverseKGroup(ListNode* head, int k) {
    //这么写在[4,5,6]的时候返回[4]的原因是 一边遍历一边倒序，导致在不到k的时候返回的head的next是null。
    ListNode* pre=nullptr,*cur=head,*nxt;
    for (int i = 0; i< k; i++){
        if(!cur) return head;
        nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    if(!cur){//这时cur已经在K+1位置了
        return pre;
    }
    head->next = reverseKGroup(cur, k);
    return pre;
}
ListNode* createListSmart(std::vector<int> v){
    //智能指针写节点next是普通指针的链表有点问题，
    int n = v.size();
    std::shared_ptr<ListNode> nxt;
    for (int i = n-1; i >= 0; --i) {
        std::shared_ptr<ListNode> temp(new ListNode(v[i]));
        temp->next = nxt.get();
        nxt =  std::move(temp); //在这一步会使上一个节点销毁。
        std::cout << v[i]<< std::endl;
    }
    return nxt.get();
}
ListNode* createList(std::vector<int> v) {
    int n = v.size();
    ListNode* nxt = nullptr;
    for (int i = n-1; i >= 0; --i){
        auto* temp = new ListNode(v[i]);
        temp->next = nxt;
        nxt = temp;
    }
    return nxt;
}
void showList(ListNode* root){
    while(root){
        std::cout << root->val << " ";
        root = root->next;
    }
    std::cout<<std::endl;
}
void test(){
    std::vector<int> v= {3,4,4,4,4};//{1,2,3,4,5}
    ListNode* root = createList(v);
    showList(root);
    ListNode* new_root = reverseKGroup(root,3);
    showList(new_root);
}
}

#endif //LEETCODE_25_REVERSE_KGROUP_H
