#ifndef MAIN_CPP_MYMATH_H
#define MAIN_CPP_MYMATH_H
#include <iostream>
#include <vector>
using namespace std;
namespace myMath_h{

    template<typename T, typename T2>
    T2 gcd(T bigger , T2 smaller){
        if(smaller == 0 ) return bigger;
        else return gcd(smaller, bigger%smaller);
    }
    long long Combination_single_time(int a, int n){
        //Ca,n = Ca,n-1 + Ca-1,n-1 ,二维dp数组如下图，因此可以压缩到一列v[a]，从上到下更新v（滚动数组参考语雀01背包问题）
        // ，第一轮对应n=2，每一轮是下一个n，但注意v[a]的范围只有0到min(a,curr_n)。不太好压缩到一行v[n]，因为两个Source是同一个地方
        //   0 1 2 ... n-1 n
        //a-1           S
        //               \
        //a             S-T
        if(2*a> n) a = n-a;
        if(a == 0 || n <= 1) return 1;
        else if (a == 1) return n;
        vector<long long> v(a+1,0); //v[x] represents Cx-1, n， 第一轮n=1,下一轮++n
        v[0]=1;
        v[1]=1; // C0,1 = C1,1 = 1
        for(int j= 2; j<n;j++){ //Ci,j = Ci-1,j-1 + Ci,j-1, v is one dimension dp.
            for(int i = min(j,a); i>0; i--){
                v[i]+=v[i-1];
            }
        }
        //j ==n
        return v[a]+v[a-1];
    }
    class Combination{
    private:
        vector<vector<long long>> C;// _C[n][x] means Cn,x = n!/(x!*(n-x)!)
        long long MOD = 0;
        bool MOD_open = false;
        int _max_n = -1;
        void dilate_to(int N){
            for (int i = _max_n + 1; i <= N; ++i) {
                C.emplace_back(i + 1, 0);
                C[i][0]= C[i][i]=1;
                for(int j = 1; 2*j <= i;++j){
                    if (MOD_open) C[i][j] = C[i][i - j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
                    else C[i][j] = C[i][i - j] = C[i - 1][j] + C[i - 1][j - 1];
                }
            }
            _max_n = N;
        }
    public:
        Combination(int n = 10, long long mod = -1){
            if(mod != -1){
                MOD_open = true;
                MOD = mod;
            }
            C.emplace_back(1, 1);//add one 1 into C, stands for C0,0
            C.emplace_back(2, 1);//add two 1 into C, stands for C1,0, C1,1
            _max_n = 1;
            dilate_to(n);
        }
        ~Combination(){
            for(int i = 0 ; i<=_max_n;++i){
                C[i].clear();
            }
            C.clear();
        }
        long long get_combination(int n, int a){
            if(n > _max_n) dilate_to(n);
            return C[n][a];
        }
    };
}
#endif //MAIN_CPP_MYMATH_H
