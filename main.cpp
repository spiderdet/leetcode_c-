
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
#include "utils/utils.h"
#include "utils/show_anything.h"
#include <functional>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <iostream>
#include <vector>
#include "calculator.h"
//#define DEBUG
using namespace std;
#define _for(i,a,b) for(int i = a; i<b;++i)

bool comp(const pair<int,int>& a,const pair<int,int>& b ){return a.first<b.first;}
template<typename _comp>void func(_comp comp);
class Base{
public:
    virtual void func(){cout << "in A" <<endl;}
};
class Derived: public Base{
public:
    virtual void func() override{cout << "in B " << endl;}
};
int main()
{
//    pair<int,int> arr[30];
//    random_device rd;
//    default_random_engine eng(rd());
//    uniform_int_distribution<int> dis(1,10);
//    int count[10] = {0}, temp;
//    _for(i,0,30){
//        temp = dis(eng);
//        arr[i]=pair<int,int>(temp,count[temp-1]++);
//    }
//    for(auto &a:arr){
//        cout << a.first << " " << a.second << ", ";
//    }
//    cout << endl;
//    sort(arr,arr+30,comp);
//    stable_sort()
//    for(auto &a:arr){
//        cout << a.first << " " << a.second << ", ";
//    }
//    cout << endl;

//    unordered_map<int,int> m = {{1,0},{9,0},{7,0},{2,0},{3,0},{5,0},{4,0},{6,0},{8,0}};
//    for(auto it=m.begin();it!=m.end();it++ ){
//        cout << it->first << " "  << it->second << endl;
//    }
    test_without_brackets();
}