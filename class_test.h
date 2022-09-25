//
// Created by 47219 on 2022/8/28.
//

#ifndef LEETCODE_CLASS_TEST_H
#define LEETCODE_CLASS_TEST_H
#include <iostream>
#include <vector>
using namespace std;
class A{
public:
    int x, y;
//    int & z;
    A(int a=1, int b=1):x(a){
        y = this->x;
        cout << "A constructor"<< endl;
//        z = 1;
    }
    A(const A& a):x(a.x),y(a.y){cout <<"A copy" << endl;}
};
class B:public A{

public:
    int z;
    B(int a =1):z(a){cout << "B constructor"<< endl;}
};
class TestClass
{
public:
    void func(int data) { printf("data: %d\n", data); }
//    void func(double data)=delete;
};
#endif //LEETCODE_CLASS_TEST_H
