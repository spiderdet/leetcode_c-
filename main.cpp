#include <ratio>
#include <typeinfo>
#include <random>
#include <string>
#include <list>
#include <stack>
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
#include <memory>
//#include <winsock2.h> //debug会报错
#include "utils/input_helper.h"
#include "utils/myAlgorithm.h"
//#define DEBUG
using namespace std;

#define _for(i,a,b) for(int i = a; i<b;++i)
//class A{
//public:
//    int a, b;
//    explicit A(int x=0, int y=0):a(x),b(y){}
//    A(const A& other):a(other.a),b(other.b){cout << "A copy\n";}
//    void set(int x, int y){a = x; b= y;}
//    void show() const{cout << a << ' ' << b <<endl;}
//};
//struct Foo {
//    Foo() { std::cout << "Constructed" << std::endl; }
//    Foo(const Foo &) { std::cout << "Copy-constructed" << std::endl; }
//    Foo(Foo &&) { std::cout << "Move-constructed" << std::endl; }
//    ~Foo() { std::cout << "Destructed" << std::endl; }
//};
//Foo f1() {
//    Foo foo;
//    return foo;
//}
//Foo f2() {
//    return Foo();
//}
//Foo f3() {
//    return {};
//}
//void f_throw() {
////    Foo foo;
//    cout << "................\n";
////    throw foo;
//    throw Foo();
//}
//
//int& foo(int& i);
//float foo(float& f);
//auto func(int a, int b) -> decltype(foo(a)){}
//template <class T>
//auto transparent_forwarder(T& t) -> decltype(foo(t)) {
//    return foo(t);
//}

int main()
{
//    Foo foo1 = f1();
//    cout << "#######################\n";
//    Foo foo2 = f2();
//    cout << "#######################\n";
//    Foo foo3 = f3();
//    cout << "#######################\n";

//    vector<A> a ={{1,2},{2,0}};
//
//    A b[3]={{1,2},{4,2},{1,4}};
//    int size = 10;
////    A * a = new A[size](1,3); //Array 'new' cannot have initialization arguments
//    unique_ptr<A[]> AO = make_unique<A[]>(size);
//    (AO.get()+2)->b = 2; //get得到的是指针
//    (AO.get()+10)->b = 2; //
//    AO[2].a=1;AO[2].show();
////    shared_ptr<A[]> A1 = make_shared<A[]>(size); 会报错！因为make_shared还没有支持A[]
//    shared_ptr<A[]> A1(new A[size]);
//    shared_ptr<A[]> A2(new A[size], [](A* p){delete [] p;});
//    shared_ptr<A[]> A3(new A[size], std::default_delete<A[]>());
//    A1[2].a=2;A1[2].show();
//    A2[2].a=3;A2[2].show();
//    A3[2].a=4;A3[2].show();


}