//树状数组，支持三个函数，从数组构造、区间查询、单点更新

#ifndef MAIN_CPP_BINARY_INDEXED_TREE_H
#define MAIN_CPP_BINARY_INDEXED_TREE_H
#include <iostream>
#include "show_anything.h"
#include <vector>
//#include <>
using namespace std;
#define DEBUG
namespace BIT_h{
    //适用于BIT的type T的node class. 默认构造函数初始化为0，重载+ += <<, 如果要适用于BIT2差分数组，还得重载-,-=
    class node{
        int value;
    public:
        node(int x):value(x){}
//如果上面的单参数构造函数用了explicit修饰，会报错 error: converting to 'node' from initializer list
// would use explicit constructor 'node::node(int)'
        node():node(0){}//委托构造，保证默认构造函数value=0
        node operator+(const node& other) const{return node(value + other.value);}
        node operator-(const node& other) const{return node(value - other.value);}
        node& operator+=(const node& other) {value += other.value; return *this;}
        node& operator-=(const node& other) {value -= other.value; return *this;}
        friend ostream& operator<<(ostream& os, const node& obj);
    };
    ostream& operator<<(ostream& os, const node& obj){os<< obj.value; return os;}

    //T这个类型需要默认值为0，即默认构造函数会初始化为0才行，然后需要重载+,+=,<< 如果想实现区间最大值而不是区间和，那就重载+即可
    //该BIT是单点更新、区间查询。更新第0个数，查询[0:1]这两个数之和。对外接口都是从0开始的！
    template<typename T> class BIT{
    private:
        vector<T> C; //从1开始，0空着
        int n;
    public:
        inline static int lowbit(int x){return x&(-x);}
        explicit BIT(int size=0):n(size){C.clear();C.resize(n+1);}
        explicit BIT(vector<T>& A){//用原数组A初始化树状数组C，C[0]空缺，从1开始计数
            construct_from_vec(A);
        }
        void construct_from_vec(vector<T>& A){
            int nA = A.size();
            if(nA==0){
                cout << "A is empty\n";
                return;
            }
            C.clear(); C.resize(nA+1);
            n = nA;
            for(int i =0; i<n;++i){
                increment(i, A[i]);
            }
#ifdef DEBUG
            show_anything_h::show_vector(A,"Original array A is\n");
            show_C();
#endif
        }
        void increment(int i, T value){//A[i]增加value，i从0算起.注意不是A[i]设为value而是增加value
            if(i<0 || i>=n){
                cout << "i : " << i << " is out of range: [0," << n-1 << "] \n";
                return ;
            }
            i++; //对于C来说是从1开始，所以i++
            while(i<=n){
                C[i]+=value;
                i += lowbit(i);
            }
#ifdef DEBUG
            show_C();
#endif
        }
        T query(int i){//计算A[0:i]左右双闭区间的区间和，
            if(i<0) return 0;
            if(i>=n ) i = n-1;
            i++;
            T result = C[i];
            i -= lowbit(i);
            while(i){
                result += C[i];
                i -= lowbit(i);
            }
            return result;
        }
        void show_C(){
            show_anything_h::show_vector(C,"BIT C is");
        }
    };
    //区间更新，单点查询的BIT2，用差分数组即可！这样可以让区间更新变成两个端点的单点更新，而单点查询变成区间查询。 然后调用BIT。本质是一个适配器。
    template<typename T> class BIT2{
    private:
        int n;
        BIT<T> bit;
    public:
        explicit BIT2(int size):n(size),bit(size){}//成员变量是对象的必须在初始化列表初始化！
        explicit BIT2(vector<T>& A):n(A.size()),bit(n){
            vector<T> A_diff;
            T last;
            for(auto c : A){
                A_diff.push_back(c-last);
                last = c;
            }
//            bit(A_diff);//调用构造函数只能在初始化的时候！必须在初始化列表里
            bit.construct_from_vec(A_diff);//所以这里用了bit的public非构造函数，bit自己构造函数(vector)的时候也可以调用这个普通函数，实现复用。
        }
        void increment(int start, int closed_end, int value){
            //和BIT一样，更新越界会告知并终止
            if(start < 0 || closed_end >= n || start > closed_end){
                cout << "[start,closed_end]: ["<<start<<", "<<closed_end<<"] is out of range, [0, " << n-1 << "] is accepted. Plus, start <= closed_end";
                return;
            }
            bit.increment(start,value);
            if(closed_end != n-1) bit.increment(closed_end+1, -value);//end是最后一个元素就不用更新右端点
        }
        T query(int i){  //单点查询其实是差分数组的[0:i]区间和查询，和BIT一样，查询越界正常返回
            if(i<0) return 0;
            if(i>=n ) i = n-1;
            return bit.query(i);
        }
    };
}
#endif //MAIN_CPP_BINARY_INDEXED_TREE_H
