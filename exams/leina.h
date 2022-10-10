// include本文件后，main函数中运行以下函数可以测试。
// test_problem1();
// test_problem2();
// test_problem3();
#ifndef MAIN_CPP_LEINA_H
#define MAIN_CPP_LEINA_H
#include <map>
#include <iostream>
#include <vector>
using namespace std;
//#######################第一题########################
typedef tuple<int,int,int> TP;
//TP代表<第k小的值，下一个要考虑的数在数列1里的序号，下一个要考虑的数在数列2里的序号>
TP median_recursive(vector<int>& nums1, vector<int>& nums2, int p1, int p2, int k){
    int m = nums1.size(), n = nums2.size();
    if(p1>=m) return {nums2[p2+k-1],p1,p2+k}; //用花括号参数列表减少拷贝次数
    if(p2>=n) return {nums1[p1+k-1],p1+k,p2};
    //上面可以直接用花括号参数列表，下面这句不可以，因为得是对象。
    if(k==1) return nums1[p1]>nums2[p2] ? TP(nums2[p2],p1,p2+1) : TP(nums1[p1],p1+1,p2);
    int temp_k = k/2, temp_k1, temp_k2;
//法1：防止某区间长度不到temp_k，取完最小值后数组1、2都取这么多，缺点是筛选效率不高，
//    temp_k = min(temp_k,int(min(nums1.size(),nums2.size())));
//法2：可以保持多的那边不变。就像下面的实现方式，将temp_k1, temp_k2分开，筛选效率略高于上面的方式
//    temp_k1 = min(temp_k, m-p1); temp_k2 = min(temp_k,n-p2);
//法3：也可以少的那边留给多的那边名额！但这样实现稍微复杂了点，
    if(m-p1<temp_k) {
        temp_k1 = m-p1;
        temp_k2 = k-temp_k1;
    }else if(n-p2 < temp_k){
        temp_k2 = n-p2;
        temp_k1 = k-temp_k2;
    }
    else temp_k1=temp_k2=temp_k;

    if(nums1[p1+temp_k1-1] > nums2[p2+temp_k2-1]) return median_recursive(nums1,nums2,p1,p2+temp_k2,k-temp_k2);
    else return median_recursive(nums1,nums2,p1+temp_k1,p2,k-temp_k1);
}
double median(vector<int>& nums1, vector<int>& nums2){
    int m = nums1.size(), n = nums2.size();
    bool even_length = (((m+n)&1)==0);
    int k = (m+n+1)/2, next1 = INT32_MAX, next2 = INT32_MAX;
    double result=0;
    TP temp = median_recursive(nums1,nums2,0,0,k);
    result += get<0>(temp);
    //不管总长度是奇是偶，肯定是要第(m+n+1)/2这个数的，如果是偶，额外还要下一个数，
    //下一个数可能来自本数列也可能来自另一个数列，另外两个数列可能都已经到末位了得考虑到
    if(even_length){
        if(get<1>(temp)<m) next1 = nums1[get<1>(temp)];
        if(get<2>(temp)<n) next2 = nums2[get<2>(temp)];
        result = (result + min(next1, next2))/2;
    }
    return result;
}
// A = [1,2,3,4,5]
// A2 = [1,2,3,4,5,6]
// b = A[(size()-1)/2]
// b2 = (b + b.next) /2
void test_problem1(){
    vector<int> v1 = {1}, v2 = {2,3,4,5,6,7}, v3={1,2},v4={-1,3}, v5={1,2},v6={3,4}, v7={},v8={1,2};
    cout << "第一题测试\n";
    cout << median(v1,v2) << " "<< median(v3,v4) << " "<< median(v5,v6) << " "<< median(v7,v8) << " ";
    cout << endl;
}
//#######################第二题########################
int find_x(int num1, int num2){
    int x = 0, num1_nums_of_1s = 0,num2_nums_of_1s = 0, temp_num1 = num1, scanner, count=0;
    while(num2){
        num2 = (num2&(num2-1));
        num2_nums_of_1s++;
    }
    while(temp_num1){
        temp_num1 = (temp_num1&(temp_num1-1));
        num1_nums_of_1s++;
    }
    if(num1_nums_of_1s == num2_nums_of_1s) return num1;
    else if(num1_nums_of_1s > num2_nums_of_1s){
        scanner = 1<<30;
        while(count<num2_nums_of_1s){
            if((scanner & num1) != 0 ){
                x += scanner;
                count++;
            }
            scanner >>= 1;
        }
        return x;
    }
    else{
        int zero_nums = num2_nums_of_1s - num1_nums_of_1s;
        x = num1;
        scanner = 1;
        while(count < zero_nums){
            if((scanner & num1) == 0){
                x += scanner;
                count++;
            }
            scanner <<= 1;
        }
        return x;
    }
}
void test_problem2(){
    int a1=3, a2 =5, a3=1,a4=12,a5=13,a6=1;
    cout << "第二题测试\n";
    cout <<find_x(a1,a2) << " "<< find_x(a3,a4) << " "<< find_x(a5,a6) << " ";
    cout << endl;
}
//#######################第三题########################
long long merge_count(vector<int>& v,vector<int>& aux, int left, int right, int diff){
    if(left >= right) return 0;
    if(left == right - 1){
        long long result = 0, temp;
        if(v[left]<=v[right]+diff) result=1;
        if(v[left]>v[right]){
            temp = v[left];
            v[left] = v[right];
            v[right] = temp;
        }
        return result;
    }
    int middle = left+(right-left)/2;
    long long result =0;
    result = merge_count(v,aux,left, middle,diff);
    result += merge_count(v,aux, middle+1, right,diff);
    int p1 = middle, p2 = right, p3;
    while(p1 >= left && p2 > middle){
        if(v[p1]<=v[p2]+diff) p2--;
        else{
            result+=right-p2;
            p1--;
        }
    }
    if(p2 == middle){
        result+= (long long)(p1-left+1)*(right-middle);
    }
    p1 = middle, p2 = right, p3 = right;
    while(p1 >= left && p2 > middle){
        if(v[p1]>v[p2]) aux[p3--] = v[p1--];
        else aux[p3--] = v[p2--];
    }
    if(p2==middle){
        while(p1>=left) aux[p3--] = v[p1--];
    }
    else{
        while(p2>middle) aux[p3--] = v[p2--];
    }
    //copy aux to v
    for(int i = left; i <= right; ++i){
        v[i]=aux[i];
    }
    return result;
}
long long num_of_pairs(vector<int>& nums1, vector<int>& nums2, int diff) {
    int n = nums1.size();
    vector<int> aux;
    for(int i = 0; i <n;++i){
        nums1[i] -= nums2[i];
    }
    aux.resize(n);
    return merge_count(nums1,aux,0,n-1,diff);
}
void test_problem3(){
    vector<int> v1={3,2,5}, v2 = {2,2,1}, v3={3,-1},v4={-2,2};
    int diff1 = 1, diff2 = -1;
    cout << "第三题测试\n";
    cout << num_of_pairs(v1,v2,diff1) << " "<< num_of_pairs(v3,v4,diff2) << " ";
    cout << endl;
}
#endif //MAIN_CPP_LEINA_H