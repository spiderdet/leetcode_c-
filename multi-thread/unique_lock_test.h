//
// Created by 47219 on 2022/8/28.
//

#ifndef LEETCODE_MULTITHREAD_TEST_H
#define LEETCODE_MULTITHREAD_TEST_H
#include <atomic>
#include <tuple>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>
#include <iostream>
using namespace std;
mutex mtx;
condition_variable cv;

void print_block (int n, char c)
{
//    unique_lock<mutex> lck (mtx);
    mtx.lock();
    for (int i=0; i<n; ++i)
    {
        cout << c;
    }
    cout << endl;;
    mtx.unlock();
}

void A(int n, char c){
    unique_lock<mutex> lck(mtx);
//    cout << "after lck\n";
    for(int i = 0; i<n;++i){
        cout << c;
    }
    cout << endl;
}
void test(){
    std::thread th1 (print_block, 50, '*');
    std::thread th0 (A, 50, '(');
    std::thread th2 (print_block, 50, '$');
    cv.notify_one();


    th0.join();
    th1.join();
    th2.join();
}
#endif //LEETCODE_MULTITHREAD_TEST_H
