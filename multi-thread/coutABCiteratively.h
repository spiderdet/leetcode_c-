//
// Created by 47219 on 2022/9/11.
//

#ifndef LEETCODE_COUTABCITERATIVELY_H
#define LEETCODE_COUTABCITERATIVELY_H
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
using namespace std;

void print_id(int id, int n_thread, int print_times,int &token, mutex& mtx, condition_variable& cv){
    char temp = 'A' +id;
    for(int i = 0; i< print_times ;++i) {
        unique_lock<mutex> lck(mtx);
        cv.wait(lck, [&id, &token]() { return id == token; });
        cout << temp << " ";
        token = (token + 1) % n_thread;
        lck.unlock();
        cv.notify_all();
    }
}

void coutABCiteratively(){
    mutex mtx;
    condition_variable cv;
    int n_thread = 3, print_times = 10;
    int token = 0; // start from token
    vector<thread> v;
//    for(int i = 0; i < n_thread; ++i){
//        v.emplace_back(print_id, i, n_thread, print_times,ref(token), ref(mtx), ref(cv));
//        //添加到vector中时已然启动线程。
//    }
    thread ths[3];
    int i = 0;
    for(auto & th: ths){
        th = thread(print_id, i, n_thread, print_times,ref(token), ref(mtx), ref(cv));
        ++i;
        //添加到vector中时已然启动线程。
    }
    for(auto & th: ths){
        th.join();
    }
//    for(auto & th: v){
//        th.join();
//    }
}
#endif //LEETCODE_COUTABCITERATIVELY_H
