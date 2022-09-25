//
// Created by 47219 on 2022/9/11.
//

#ifndef LEETCODE_CHILD_MAIN_PRINT_ITERATIVELY_H
#define LEETCODE_CHILD_MAIN_PRINT_ITERATIVELY_H
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
using namespace std;
mutex mtx;
condition_variable cv;
int token = 0;

void func(string name, int times){
    int id;
    if(name == "child"){
        id = 0;
    }
    else id = 1;
    unique_lock<mutex> lck(mtx);
    cv.wait(lck, [&](){return id == token;});
    for(int i = 0; i< times; ++i){
        cout << "this is " << name << endl;
    }
    token = (token+1)%2;
    lck.unlock();
    cv.notify_all();
}
void child_main_print_iteratively(){
    int id = 1, child_times = 3, main_times = 4, total_times = 3;
    for(int i =0 ; i< total_times;++i){
        thread child_th(func,"child", child_times);
        unique_lock<mutex> lck(mtx);
        cv.wait(lck, [&](){return id == token;});
        for(int j = 0; j < main_times; ++j){
            cout << "this is " << "main" << endl;
        }
        token = (token+1)%2;
        lck.unlock();
        cv.notify_all();
        child_th.join();//别忘了join!!
    }
}
#endif //LEETCODE_CHILD_MAIN_PRINT_ITERATIVELY_H
