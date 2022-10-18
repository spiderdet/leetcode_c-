#ifndef MAIN_CPP_MYMATH_H
#define MAIN_CPP_MYMATH_H
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
namespace myMath_h{
    //组合数类、单次求组合数
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

    //质数类、单次判断是否是质数
    template<typename T> bool isPrime_single(T n){
        if(n<=1){
            cout << "n <= 1!\n";
            return false;
        }
        if(n<=3) return true;
        for(T i =2;i*i<=n;i++){
            if(n%i==0) return false;
        }
        return true;
    }
    class Prime{//is_prime判断是否为质数，extend_primes用于扩展质数列表直到back()^2大于n，两个函数相互调用
    private:
    public:
        static vector<long long> primes_list;
        Prime()= default;
        void extend_primes(long long n){
            int candidate = primes_list.back() + 2;
            for(;candidate*candidate<=n;candidate+=2){
                if(is_prime(candidate)) primes_list.push_back(candidate);
            }
        }
        bool is_prime(long long n){
            if(n > pow(primes_list.back(),2)) {extend_primes(n);}
            if(n <= primes_list.back()){
                return lower_bound(primes_list.begin(),primes_list.end(),n)!=primes_list.end();
            }
            // n > primes_list.back() and n <= primes_list.back()^2
            for(auto c : primes_list){
                if(n % c == 0) return false;
            }
            return true;
        }
    };

    //模p乘法逆元的3种求法：快速幂，Exgcd，线性递推（逆元类）
    vector<long long> Prime::primes_list = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    template<typename T> T fast_powers(T base_, T exp_, T MOD_NUM = 1e9 + 7){//calculate (base^n) % MOD_NUM
        //exp_=MOD_NUM-2 can be used to calculate 'mod p multiplication inverse element' 见语雀-算法题 数学-模p乘法逆元
        T result = 1;
        while(exp_){
            if(exp_ & 1) result = result * base_ % MOD_NUM;
            exp_ >>= 1;
            base_ = base_ * base_ % MOD_NUM; //multiplier也要mod！
        }
        return result;
    }
    template<typename T> T gcd(T x, T y){
        /* Euclid GCD, set y, x%y as next x, y until y==0, return current x is gcd. x,y can be negative,
         * return value also can be negative! x%y = x-(x/y)*y, x/y is sign |x/y|
         *      x   y   x%y
         *      24  -32 24
         *      -32 24  -8
         *      24  -8  0
         *      -8  0
         */
        T r;
        while(y){
            r = x % y;
            printf("x:%d,y:%d,x%y:%d\n",x,y,r);
            x = y;
            y = r;
        }
        return x;
    }
    /** Compute ax+by=gcd(a,b), return value is gcd(a,b), can be negative
     * Why it's called Ex-gcd is that the solution of x and y is computed during the process of computing
     * gcd of a and b. It's the second method to calculate 'mod p multiplicative inverse element',
     * e.g. (a*x)%p=1 then x is inverse of a mod p, the solution x of ax-py=1 is the inverse. x belongs to
     * (-p,p), so to make sure x belongs to [0,p): (x+p)%p
     * @tparam T type of a,b,x,y and gcd(a,b)
     * @param a
     * @param b
     * @param x reference type, the solution x of the equation is stored in this variable
     * @param y reference type, the solution y of the equation is stored in this variable
     * @return gcd(a,b), can be negative,
     */
    template<typename T> T Exgcd(T a, T b, T &x, T &y) {
        //用于求逆元时注意x<0的情况，得(x+p)%p
        if (!b) {
            x = 1;
            y = 0;
            return a;
        }
        T d = Exgcd(b, a % b, x, y);
        T t = x;
        x = y;
        y = t - (a / b) * y;
        return d;
    }
    template<typename T> class multiplicative_inverse_modp_linear_recursion{
    private:
        T _current_n;
        T _modulus;
        bool _modulus_not_prime;
    public:
        vector<T> inv;
        multiplicative_inverse_modp_linear_recursion(T modulus): inv({0, 1}), _current_n(1), _modulus(modulus){
            if(modulus <= 2) cerr << "modulus=" << _modulus << ", too small\n";
            else{
                _modulus_not_prime = ! isPrime_single<T>(modulus);
            }
        }
        void enlarge_to(T n){// enlarge inv until inv(n)
            if(n <= _current_n) return;
            if(n >= _modulus) n = _modulus-1;
            for(T i=_current_n+1; i<=n; ++i){
                if(_modulus_not_prime && _modulus%i == 0){
                    inv.push_back(0);
                    _current_n++;
                }else{
                    inv.push_back((_modulus - _modulus / i) * inv[_modulus % i] % _modulus);
                    _current_n++;
                }
            }
        }
        T get_inverse_of(T ele){
            if(ele >= _modulus) ele %= _modulus;
            else if(ele <= 0){
                cerr << "input <= 0, should be > 0\n";
                return 0;
            }
            enlarge_to(ele);
            return inv.at(ele);
        }
    };
    void test_3methods_of_multiplicative_inverse_modp(){
        int x,y, p = 13;
        multiplicative_inverse_modp_linear_recursion<int> m(p);
        for(int i = 1; i< p;i++){
            Exgcd<int>(i,p,x,y); // (x+p)%p
            cout << fast_powers(i,p-2,p) << ' ' << (x+p)%p << ' ' << m.get_inverse_of(i) << endl;
        }
    }
}
#endif //MAIN_CPP_MYMATH_H
