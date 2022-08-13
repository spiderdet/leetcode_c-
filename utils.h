//
// Created by 47219 on 2022/7/11.
//

#ifndef LEETCODE_UTILS_H
#define LEETCODE_UTILS_H
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
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
        if(!message.empty()) cout << message<<endl;
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
    template<typename T>
    void delete_all_targets(vector<T>& nums, T target){
        auto slow = nums.begin(), fast = nums.begin();
        T swap_temp;
        while(fast != nums.end()){
            if(*slow == target){
                while(*fast==target){
                    ++fast;
                }
                swap_temp = *slow;
                *slow = *fast;
                *fast = swap_temp;
            }
            ++fast;
            ++slow;
        }
        nums.erase(slow,nums.end()); //为啥用iterator就是为了方便删除末尾那些target
    }
    template<typename T, typename T2>
    T2 gcd(T bigger , T2 smaller){
        if(smaller == 0 ) return bigger;
        else return gcd(smaller, bigger%smaller);
    }
    long long Combination_single_time(int a, int n){
        //Ca,n = Ca,n-1, Ca-1,n-1
        if(2*a> n) a = n-a;
        if(a == 0 || n <= 1) return 1;
        else if (a == 1) return n;
        vector<long long> v(a+1,0); //v represents Ca,0, next v represents Ca,1
        v[0]=1;
        v[1]=1; // C0,1 = C1,1 = 1
        for(int j= 2; j<n;j++){ //Ci,j = Ci-1,j-1 + Ci,j-1, v is one dimension dp.
            for(int i = min(j,a); i>0; i--){
                v[i]+=v[i-1];
            }
        }
        //j ==n
        return v[a]+v[a-1];
    }
    class Combination{
    private:
        vector<vector<long long>> C;// _C[n][a] means Ca,n = n!/(a!*(n-a)!)
        long long MOD = 0;
        bool MOD_open = false;
        int _max_n = -1;
        void dilate_to(int N){
            for (int i = _max_n + 1; i <= N; ++i) {
                C.emplace_back(i + 1, 0);
                C[i][0]= C[i][i]=1;
                for(int j = 1; 2*j <= i;++j){
                    if (MOD_open) C[i][j] = C[i][i - j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
                    else C[i][j] = C[i][i - j] = C[i - 1][j] + C[i - 1][j - 1];
                }
            }
            _max_n = N;
        }
    public:
        Combination(int n = 10, long long mod = -1){
            if(mod != -1){
                MOD_open = true;
                MOD = mod;
            }
            C.emplace_back(1, 1);
            C.emplace_back(2, 1);
            _max_n = 1;
            dilate_to(n);
        }
        ~Combination(){
            for(int i = 0 ; i<=_max_n;++i){
                C[i].clear();
            }
            C.clear();
        }
        long long get_combination(int n, int a){
            if(n > _max_n) dilate_to(n);
            return C[n][a];
        }
    };
}
#endif //LEETCODE_UTILS_H
