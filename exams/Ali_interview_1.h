//
// Created by 47219 on 2022/8/24.
//

#ifndef LEETCODE_ALIBABA_1_H
#define LEETCODE_ALIBABA_1_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;
inline bool is_alpha(char c){return (c >='a' && c<='z') || (c>='A' && c<='Z');}
void copy(string& s, int & target_start, int &source_start, int source_end){
    for(int i= source_start; i < source_end;i++){
        s[target_start++] = s[i];
    }
}
string extract_consecutive_three_char(string s){
    int n = s.length();
    int set = 0, head = 0, traverse = 0, count = 0;
    //find the first non-alpha 因为不需要保留前面的字符，如果前面的字符只有两个比如，ab00abc那也要删去，所以不用这一段！
//    while(traverse<n){
//        if(is_alpha(s[traverse])){
//            ++set;
//            ++traverse;
//        }
//        else {
//            break;
//        }
//    }
    while(traverse < n){
        if(is_alpha(s[traverse])){
            ++count;
            if(count == 1){
                head = traverse;
            }
        }
        else if (count >= 3){
            //copy [head,traverse) to [set
            copy(s,set,head, traverse);
            count = 0;
        }
        else {count = 0;}
        ++traverse;
    }
    //
    if(count > 0){
        copy(s, set, head, traverse);
    }
    return s.substr(0,set);

}

void test(){
    vector<string> a = {"ab",
                        "",
                        "abcd",
                        "0000",
                        "0",
                        "ab00abc",
                        "abcc00abcc",
                        "abc0001ab000abc0",
                        "00abcs",
                        "00abcs0000",
                        "0ab0abc000abcd000abcde0"};
    for(auto & c : a){
        cout << c << endl;
        cout << extract_consecutive_three_char(c) << endl;
    }
}
#endif //LEETCODE_ALIBABA_1_H
