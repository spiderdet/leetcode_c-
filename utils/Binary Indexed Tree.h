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
    //适用于BIT的type T的node class. 默认构造函数初始化为0，重载+和+=

    //T这个类型需要默认值为0，即默认构造函数会初始化为0才行，然后需要重载+, 如果想实现区间最大值而不是区间和，那就重载+即可
    template<typename T> class BIT{
    private:
        vector<T> C; //从1开始，0空着
        int n;
    public:
        inline static int lowbit(int x){return x&(-x);}
        BIT(vector<T>& A){//用原数组A初始化树状数组C，C[0]空缺，从1开始计数
            int nA = A.size();
            if(nA==0){
                cout << "A is empty\n";
                return;
            }
            C.clear(); C.resize(nA+1);
            n = nA;
            for(int i =0; i<n;++i){
                add(i,A[i]);
            }
#ifdef DEBUG
            show_anything_h::show_vector(A,"Original array A is\n");
            show_C();
#endif
        }
        void add(int i, T value){//A[i]增加value，i从0算起.注意不是A[i]设为value而是增加value
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
//        BIT(vector<T>& A){ //另一个初始化C的方式，但很麻烦，不如上面的方法调用add
//            int nA = A.size();
//            if(nA==0){
//                cout << "A is empty\n";
//                return;
//            }
//            C.resize(nA+1);
//            n = nA;
//            T temp_value;
//            int temp_i, prefix;
//            for(int i = 1; i<= n;++i){
//// 以i=1011000为例，C[i]=A[i-1]+C[1010100]+C[1010110]+C[1010111],即去除尾1后把下一位设为1，
//// 然后不断把尾1后的0设为1直到最后一位是1
//                temp_value = A[i-1];
//                temp_i = i;
//                if((temp_i&1) ==1) {
//                    C[i]=temp_value;
//                    continue;
//                }
//                prefix = temp_i & (temp_i - 1);
//                temp_i = ((temp_i-prefix)>>1) + prefix;
//                temp_value += C[temp_i];
//                while((temp_i&1) != 1){
//                    temp_i += (temp_i&(-temp_i))>>1;
//                    temp_value += C[temp_i];
//                }
//                C[i]=temp_value;
//            }
//#ifdef DEBUG
//            show_anything_h::show_vector(A,"Original array A is\n");
//            show_anything_h::show_vector(C,"BIT C is\n");
//#endif
//        }
    };
}
#endif //MAIN_CPP_BINARY_INDEXED_TREE_H
