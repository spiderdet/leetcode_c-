#ifndef MAIN_CPP_CALCULATOR_H
#define MAIN_CPP_CALCULATOR_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cassert> //为了assert
//#define DEBUG
using namespace std;
class divide_zero:public exception{
public:
    divide_zero(){}
    const char * what() const noexcept override{ cerr <<"divide by zero" <<endl;return nullptr;}
};
class unknown_input:public exception{
public:
    unknown_input(){}
    const char * what() const noexcept override{cerr << "the charactor inputed is undefined\n";return nullptr;}
};
void calcu_last_two(vector<int>& num_stack, vector<char>& op_stack){
    int temp = num_stack.back();
    num_stack.pop_back();
    switch(op_stack.back()){
        case '+':
            num_stack.back() += temp;
            break;
        case '-':
            num_stack.back() -= temp;
            break;
        case '*':
            num_stack.back() *= temp;
            break;
        case '/':
            if(temp == 0 ){
                cout << "divisor is 0! throwing exception..." <<endl;
                throw(divide_zero());
            }
            num_stack.back() /= temp;
            break;
    }
    op_stack.pop_back();
}
void pop_stack(vector<int>& num_stack, vector<char>& op_stack, map<char,int>& allowed_op, int end_priority,
               char op_enable_pop= 'n'){
#ifdef DEBUG
    cout << "The operator enables pop_stack function('n'=unknown): " << op_enable_pop <<endl;
    show_anything_h::show_vector(num_stack,"before pop_stack : num_stack:");
    show_anything_h::show_vector(op_stack,"op_stack:");
    cout <<  "end_priority: " << end_priority << endl;
#endif
    if(allowed_op.find('(')!= allowed_op.end() && end_priority==allowed_op['(']){
        while(allowed_op[op_stack.back()]>end_priority){
            calcu_last_two(num_stack,op_stack);
        }
        op_stack.pop_back();
    }
    else{
        while(allowed_op[op_stack.back()]>=end_priority){
            calcu_last_two(num_stack,op_stack);
        }
    }
#ifdef DEBUG
    show_anything_h::show_vector(num_stack,"after pop_stack : num_stack:");
    show_anything_h::show_vector(op_stack,"op_stack:");
    cout << "#########################\n";
#endif
}
int calculator_with_backets(string s){
    s = s.substr(0,remove(s.begin(),s.end(),' ')-s.begin());
#ifdef DEBUG
    cout << s << endl;
#endif
    int num = 0, n = s.size();
    vector<int> num_stack;
    vector<char> op_stack;
    map<char,int> allowed_op = {{'+',1},{'-',1},{'*',2},{'/',2},{'(',0},{')',3}};
    for(int i = 0;i<n;++i){
        if(isdigit(s[i])){
            num = num*10+(s[i]-'0');
            if(i == n-1){
                num_stack.push_back(num);
                break;
            }
        }
        else if(allowed_op.find(s[i]) != allowed_op.end()){
#ifdef DEBUG
            cout << "s[i] is op: " <<s[i] << endl;
#endif
            if(i>0 && isdigit(s[i-1])){//防止连续两个符号时把0放入数栈，比如(1+2)*(2+3)
                num_stack.push_back(num);
                num = 0;
            }
            if(s[i]=='('||op_stack.empty()){
                op_stack.push_back(s[i]);
            }
            else if(s[i] == ')'){
                pop_stack(num_stack,op_stack,allowed_op,allowed_op['('],s[i]);
            }
            else if(allowed_op[s[i]]>allowed_op[op_stack.back()]){
                op_stack.push_back(s[i]);
            }
            else{//出栈到优先级>栈顶操作符为止
                pop_stack(num_stack,op_stack,allowed_op,allowed_op[s[i]],s[i]);
                op_stack.push_back(s[i]);
            }
        }
        else{
            cout << "unknown charactor: " << s[i] <<endl;
            throw(unknown_input());
        }
    }
#ifdef DEBUG
    cout << "op_stack size: " << op_stack.size() << ", num_stack size: " << num_stack.size() << endl;
    show_anything_h::show_vector(op_stack, "op_stack:");
    show_anything_h::show_vector(num_stack, "num_stack:");
#endif
    assert(op_stack.size()+1==num_stack.size());
    while(!op_stack.empty()){
        calcu_last_two(num_stack, op_stack);
    }
    return num_stack[0];
}
int calculator_withou_brackets_2stack(string s){
    vector<int> num_stack; vector<char> op_stack;
    s = s.substr(0,remove(s.begin(),s.end(),' ')-s.begin());
    int n = s.size(), num = 0;
    map<char,int> allowed_op = {{'+',1},{'-',1},{'*',2},{'/',2}};
    for(int i =0; i<n;++i){
        if(isdigit(s[i])){
            num = num*10 + int(s[i]-'0');
            if(i == n-1){
                num_stack.push_back(num);
            }
        }
        else{//如果不是数字
            num_stack.push_back(num);
            num = 0;
            if(allowed_op.find(s[i])==allowed_op.end()){
                cout << "unknown charactor besides 0-9 and +-*/ "<<endl;
                return -1;
            }else{//如果是+-*/
                if(op_stack.empty()) op_stack.push_back(s[i]);
                else if(allowed_op[s[i]]>allowed_op[op_stack.back()]) op_stack.push_back(s[i]);
                else{
                    pop_stack(num_stack,op_stack,allowed_op,allowed_op[s[i]],s[i]);
                    op_stack.push_back(s[i]);
                }
            }
        }
    }
#ifdef DEBUG
    cout << "opstack size: " << op_stack.size() << ", num_stack size: " << num_stack.size() <<endl;
    show_anything_h::show_vector(op_stack,"opstack:");
    show_anything_h::show_vector(num_stack,"numstack:");
#endif
    assert(op_stack.size()+1==num_stack.size());
    while(!op_stack.empty()){//遍历完还有运算符的话
        calcu_last_two(num_stack,op_stack);
    }
    return num_stack[0];
}
int calculator_withou_brackets_1stack(string s) {
    vector<int> stk;
    char preSign = '+';
    int num = 0;
    int n = s.length();
    for (int i = 0; i < n; ++i) {
        if (isdigit(s[i])) {
            num = num * 10 + int(s[i] - '0');
        }
        if (!isdigit(s[i]) && s[i] != ' ' || i == n - 1) {//i==n-1也需要处理num
            switch (preSign) {
                case '+':
                    stk.push_back(num);
                    break;
                case '-':
                    stk.push_back(-num);
                    break;
                case '*':
                    stk.back() *= num;
                    break;
                default:
                    stk.back() /= num;
            }
            preSign = s[i];
            num = 0;
        }
    }
    return accumulate(stk.begin(), stk.end(), 0);
}

void test_without_brackets(){
    string s1 = "21+30*5-7";
    cout << calculator_withou_brackets_2stack(s1);
}
void test_calculator_with_brackets(){
//    string s1 = "2+((10+21*38-42)-(1+3))";
//    string s2 = "(1+3)*(4-2)";
    string s3 = "2/0";
    cout
//    << calculator_with_backets(s1) << endl
//    << calculator_with_backets(s2) << endl
            << calculator_with_backets(s3) << endl
            ;
}

bool addition_overflow(int a , int b){
    //INT_MIN比-INT_MAX还要小1！所以ab都正和ab都负要分开来考虑
    if(a>0 && b>0) return INT32_MAX-a<b;
    if(a<0 && b<0) return INT32_MIN-a>b;
    return false; //其他所有情况都不会溢出，比如a,b任何一个为0，或者一正一负。
}
bool subtraction_overflow(int a , int b){
    if(b==INT32_MIN) return a>=0; //因为-INT32_MIN还是INT32_MIN所以需要额外考虑
    else return addition_overflow(a,-b);//否则直接-b，然后调用加法溢出判断函数即可
}
bool multiplication_overflow(int a , int b){//溢出return true而不是return false
    //要额外小心-(INT32_MIN)仍然是-2147483648，所以额外处理,包括ab其中之一是INT32_MIN，也包括a*b=INT32_MIN
    if(a == INT32_MIN) return b!=0&&b!=1;
    if(b == INT32_MIN) return a!=0&&a!=1;
    if(a<0 && b>0) return INT32_MIN/a < b;
    if(a>0 && b<0) return INT32_MIN/b < a;
    a = abs(a); b = abs(b);
    return INT32_MAX/a < b;
}
void test_overflow(){
    int a = INT32_MAX;
    int x = -a/2, y = -a/2-100, z = a/2+100;
    cout << addition_overflow(x, y) << " ";
    cout << addition_overflow(z, -x) << " ";//判断减法是否溢出可以套用加法溢出的函数
    //极限测试
    cout << INT32_MAX << " "<< INT32_MIN << " " << addition_overflow(-2000000000, 147483648)
         << " " << addition_overflow(2000000000,147483648);
    cout << endl <<"multiplication overflow test"<<endl;
    cout <<multiplication_overflow(65536,32768) << " " << multiplication_overflow(65536,-32768)
         << " " << multiplication_overflow(-65536,-32768) << " " << multiplication_overflow(INT32_MIN,1);
}
#endif //MAIN_CPP_CALCULATOR_H
