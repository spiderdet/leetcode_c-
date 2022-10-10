#include <ratio>
#include <typeinfo>
#include <random>
#include <string>
#include <list>
#include <queue>
#include <forward_list>
#include <atomic>
#include <tuple>
#include <mutex>
#include <semaphore>
#include <condition_variable>
#include <future>
#include <chrono>
#include <thread>
#include <ctime>
#include <limits>
#include <cassert>
#include "utils/utils.h"
#include "utils/show_anything.h"
#include <functional>
#include <numeric>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <iostream>
#include <vector>
#include <winsock2.h>
#include "utils/input_helper.h"
#include "utils/Binary Indexed Tree.h"
#include "utils/popcount.h"
//#define DEBUG
using namespace std;

#define _for(i,a,b) for(int i = a; i<b;++i

//class node{
//    int value;
//public:
//    node(int x):value(x){}
////如果上面的单参数构造函数用了explicit修饰，会报错 error: converting to 'node' from initializer list
//// would use explicit constructor 'node::node(int)'
//    node():node(0){}//委托构造，保证默认构造函数value=0
//    node operator+(const node& other) const{return node(value + other.value);}
//    node& operator+=(const node& other) {value += other.value; return *this;}
//    friend ostream& operator<<(ostream& os, const node& obj);
//};
//ostream& operator<<(ostream& os, const node& obj){os<< obj.value; return os;}
//

int main()
{
//    vector<pair<int,int>> temp = {{1,2},{1,4}};
//    vector<node> A = {{1},{2},{3},{4},{5},{6},{7},{8},{9}};
//    BIT_h::BIT<node> bit(A);
//    bit.add(1,2);
//    cout << bit.query(6);
//    node nd1(1),nd2(2),nd3(3);
//    cout << (nd1+=nd2)+nd3 << " " << nd1;
//    cout << __builtin_popcount(3);
}