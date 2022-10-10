#ifndef MAIN_CPP_POPCOUNT_H
#define MAIN_CPP_POPCOUNT_H
#include <iostream>
#include <numeric>
#include <ctime>
#include <random>
#include <chrono>
#include <limits> // 为了std::numeric_limits<uint32_t>::max()
using namespace std;
//一共有sparse_popcnt,lookup_popcnt_1,lookup_popcnt_2,parallel_popcnt,nifty_popcnt,
//hacker_popcnt,hacker_popcnt_2,hakmem_popcount,hakmem_popcount_64,builtin_popcnt,assembly_popcnt
int sparse_popcnt(uint32_t n){
    int count =0;
    while(n){
        ++count;
        n &= n-1;
    }
    return count;
}
# define BIT2(n)       n,       n+1,       n+1,       n+2
# define BIT4(n) BIT2(n), BIT2(n+1), BIT2(n+1), BIT2(n+2)
# define BIT6(n) BIT4(n), BIT4(n+1), BIT4(n+1), BIT4(n+2)
# define BIT8(n) BIT6(n), BIT6(n+1), BIT6(n+1), BIT6(n+2)
static const uint8_t table[256] = {BIT8(0)};
int lookup_popcnt_1(uint32_t n){
    const uint8_t* p = reinterpret_cast<const uint8_t*>(&n);
    return table[p[0]] + table[p[1]] + table[p[2]] + table[p[3]];
}
int lookup_popcnt_2(uint32_t n){
    return table[n & 0xFF] + table[(n>>8) & 0xFF] +
           table[(n>>16) & 0xFF] + table[n>>24]; //n>>24不用再与了！
}
int parallel_popcnt(uint32_t n){
    n = (n&0x55555555) + ((n>>1)&0x55555555);
    n = (n&0x33333333) + ((n>>2)&0x33333333);
    n = (n + (n>>4))&0x0F0F0F0F;//n>>4以上才可以合并，因为n>>2是在算4位里1的个数，最多4个需要用3位保存，但只能用两位保存不够。n>>4是算8位里1的个数，最多8个需要4位保存，用低4位正好。
    n = (n + (n>>8))&0x00FF00FF;
    return (n + (n>>16))&0x0000FFFF;
}
int nifty_popcnt(uint32_t n){
    //constexpr就是用来编译期计算的！减少程序员的书写量，提高可读性，同时不影响程序运行时性能！
    constexpr uint32_t max = std::numeric_limits<uint32_t>::max();
    constexpr uint32_t MASK_01010101 = max / 3;
    constexpr uint32_t MASK_00110011 = max / 5;
    constexpr uint32_t MASK_00001111 = max /17;
    n = (n & MASK_01010101) + ((n>>1) & MASK_01010101);
    n = (n & MASK_00110011) + ((n>>2) & MASK_00110011);
    n = (n + (n>>4)) & MASK_00001111;
    return n % 255 ; //原理是 B3*256^3+B2*256^2+B1*256+B0 % 255 = B3+B2+B1+B0,
    // a%b = a - (a/b)*b
}
int hacker_popcnt(uint32_t n){
    n = n - ((n>>1) &0x55555555);
    n = (n&0x33333333) + ((n>>2)&0x33333333);
    n = (n + (n>>4))&0x0F0F0F0F;
    n = n + (n>>8); //这最后三行改成n%255会更快。
    n = n + (n>>16);
    return n & 0x0000003F;
}
int hacker_popcnt_2(uint32_t n){
    n = n - ((n>>1) &0x55555555);
    n = (n&0x33333333) + ((n>>2)&0x33333333);
    n = (n + (n>>4))&0x0F0F0F0F;
    return n%255;
}
int hakmem_popcount(uint32_t n){//解释见语雀，与上面parallel思路不同，基于公式(4a+2b+c)-(2a+b)-a = a+b+c
    unsigned int tmp;
//    tmp = n - ((n>>1) & 033333333333) - ((n>>2) & 011111111111); //好，但是还不够好
    tmp = (n>>1) & 033333333333; // 为啥从上面的一句话变成这四句话，1.同一个大常量节省寄存器 2. 移1位比移2位速度快！
    n = n - tmp;
    tmp = (tmp>>1) & 033333333333; //这里可以用0x1111但因为tmp的每三位的首位为0，所以用0x333也可以，为了保证大常量只有一个
    //就用了0x3333.
    //
    n = n - tmp;
    return ((n + (n >> 3)) & 030707070707) % 63; //这个方法只能用于n的长度<=62,64位整数就没办法用这个方法了，见下面
}
int hakmem_popcount_64(uint32_t n){ // 可以修改用于 uint64_t
    //原理是(8a+4b+2c+d)-(4a+2b+c)-(2a+b)-a = a+b+c+d
    unsigned int tmp = (n>>1)&0x77777777;
    n = n - tmp;
    tmp = (tmp>>1)&0x77777777; //反复使用同一个大常量，节省寄存器
    n = n - tmp;
    tmp = (tmp>>1)&0x77777777; //复用上次结果，每次移1位比移多位快。
    n = n - tmp;
    n = (n + (n>>4)) & 0x0F0F0F0F; //至此已经8位一组代表每组里1的个数，
    //相比于接下来用 n % 255,下面用乘法和移位
    n = n * 0x01010101; //写出乘法就知道，前8位已经求和了，B3+B2+B1+B0
    return n>>24;
}
int builtin_popcnt(uint32_t n)
{
    return __builtin_popcount(n);
}
int assembly_popcnt(uint32_t n)
{
#ifdef _MSC_VER  // Intel style assembly
    __asm {
        popcnt eax,n
        mov count,eax
    }
#elif __GNUC__  // AT&T style assembly
    __asm__("popcnt %0,%%eax"::"r"(n));
#else
#error "other POPCNT implementations go here"
#endif
}
string name_list[11] = {"sparse_popcnt","lookup_popcnt_1","lookup_popcnt_2","parallel_popcnt","nifty_popcnt",
"hacker_popcnt","hacker_popcnt_2","hakmem_popcount","hakmem_popcount_64","builtin_popcnt","assembly_popcnt"};
decltype(sparse_popcnt)* func_list[11] = {sparse_popcnt,lookup_popcnt_1,lookup_popcnt_2,parallel_popcnt,
                 nifty_popcnt,hacker_popcnt,hacker_popcnt_2,hakmem_popcount,hakmem_popcount_64,
                 builtin_popcnt,assembly_popcnt};
pair<double,string> timing_one_popcnt(const int idx, vector<uint32_t>& nums){
    using namespace std::chrono;
    uint32_t loops = nums.size();
    cout << name_list[idx] << " is running\n";
    auto start = steady_clock::now();
    for(int i =0; i< loops; ++i){
        func_list[idx](nums[i]);
    }
    auto end = steady_clock::now();
    auto dur = duration_cast<duration<double>>(end-start);
    double total_time = dur.count(), single_time = total_time/loops;
    cout << "Total time : " << total_time << ", average time : " << single_time << endl;
    return {single_time, name_list[idx]};
}
void timing_all_popcnts(){
//    uint32_t num = numeric_limits<uint32_t>::max();
    int num = INT32_MAX;
//    uint32_t num = 10000;
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<uint32_t> dis(0,std::numeric_limits<uint32_t>::max());//等价于0xFFFFFFFF
    vector<uint32_t> v;
    v.reserve(num);
    for(int i =0; i< num; i++){
        v.push_back(dis(eng));
    }
    set<pair<double,string>> answer;
    for(int i =0; i <11;i++){
        answer.emplace(timing_one_popcnt(i,v));
    }
    cout << "########################\n";
    int i = 1;
    for(auto ele : answer){
        cout << i << ": "  << ele.second << " = " << ele.first << endl;
        ++i;
    }
}
#endif //MAIN_CPP_POPCOUNT_H
