#ifndef MAIN_CPP_MYALGORITHM_H
#define MAIN_CPP_MYALGORITHM_H
#include <vector>
#include <cassert>
#include "show_anything.h"
using namespace std;
namespace myAlgorithm_h{
    /**
     * inplace rotate array of [first,middle),[middle,last)
     * @param v
     * @param first
     * @param middle
     * @param last
     * @return the final place of original first element
     */
    int inplace_rotate(vector<int>& v, int first, int middle, int last){

        assert(middle<=last&& first <= middle && last<=v.size());
        int result_place = last-middle+first;
        if(middle == last && first == middle){
            return result_place;
        }
        int p1 = first, p2 = middle, temp;
        while(p2!=last){//注意是p2不是p1！就是当p1==middle并且p2==last才会跳出循环！
            temp = v[p1];
            v[p1] = v[p2];
            v[p2] = temp;
            ++p1;
            ++p2;
            if(p1 == middle) middle = p2;//核心是同类子问题，因为此时[first,middle)已经是最终位置了,而[middle,p2)和
            //[p2,last)是一个新的待旋转的子问题，因此将middle = p2。
            else if(p2 == last) p2 = middle; //一样，也是同类子问题！
        }
        return result_place;
    }
    void test_inplace_rotate(){
        vector<int> v = {1,2,3,4,5,6,7,8,9}, v2;
        v2.insert(v2.begin(),v.begin(),v.end());
        inplace_rotate(v,0,3,8);//注意最后一个元素不会考虑，因为last是取不到的！
        show_anything_h::show_vector(v);
        inplace_rotate(v2,0,6,8);
        show_anything_h::show_vector(v2);
    }


}
#endif //MAIN_CPP_MYALGORITHM_H
