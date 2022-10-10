#ifndef MAIN_CPP_INPUT_HELPER_H
#define MAIN_CPP_INPUT_HELPER_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
namespace input_helper_h{
    /**
     * convert numpy format matrix to vector<vector<int>> matrix,
     * e.g. [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
     * this function will read cin until \n or EOF, so add \n before contents afterwards if plan to read other
     * information in cin after this function.
     * @param file_in whether cin redirect to file input or not
     * @param file address of input file
     * @return a two dimensional matrix
     */
    vector<vector<int>> matrix(bool file_in = true, string file = "test_input.in"){
        if(file_in){
            string prefix = "./test_inputs/";
            freopen((prefix+file).c_str(),"r",stdin);
        }
        string s;
        cin >> s;
        s = s.substr(0,remove(s.begin(),s.end(),' ')-s.begin());
        int n = s.size(), tmp, num=0;
        vector<vector<int>> result;
        vector<int> temp;
        vector<char> stack;
        set<char> allowed_sep = {',','.'}, allowed_brackets = {'[',']','{','}','(',')'};
        map<char,char> brackets_map = {{']','['},{'}','{'},{')','('}};
        for(int i =0; i <n; ++i){
            if(isdigit(s[i])){
                num = num*10+(s[i]-'0');
                if(i == n-1){
                    temp.push_back(num);
                }
            }else if(allowed_sep.find(s[i])!=allowed_sep.end()){
                if(num == 0 && (i==0 || i >0 && !isdigit(s[i-1]))){
                    if(i>0 && brackets_map.find(s[i-1])!=brackets_map.end()){
                        continue;
                    }else{
                        cout << "Missing number before seperator, regarding as default 0." << endl;
                    }
                }
                temp.push_back(num);
                num = 0;
            }else if (allowed_brackets.find(s[i])!=allowed_brackets.end()){
                if(brackets_map.find(s[i])!=brackets_map.end()){
                    if(stack.size()>=2){
                        temp.push_back(num);
                        num = 0;
                        result.push_back(temp);
                        temp.clear();
                    }
                    stack.pop_back();
                }else stack.push_back(s[i]);
            }else{
                cerr << "unknown char other than , . () [] {} " << endl;
                return {};
            }
        }
        return result;
    }

}
#endif //MAIN_CPP_INPUT_HELPER_H
