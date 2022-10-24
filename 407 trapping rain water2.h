#ifndef MAIN_CPP_407_TRAPPING_RAIN_WATER2_H
#define MAIN_CPP_407_TRAPPING_RAIN_WATER2_H
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include "utils/input_helper.h"
using namespace std;
namespace lc407{
//#define DEBUG
    template<typename T> struct comp{
        bool operator()(const T& a, const T& b){ return get<0>(b) < get<0>(a);}//或者利用pair,tuple自己重载的<也可以
    };
    /**
     * maintain a priority_queue of borders
     * @param heightMap
     * @return maximum trapped water volume
     */
    int trapRainWater(vector<vector<int>>& heightMap){
        if(heightMap.size()<=2 || heightMap[0].size()<=2) return 0;
        int rows = heightMap.size(), cols = heightMap[0].size();
#ifdef DEBUG
        cout << "heightMap is as follows\n";
        for(int i = 0; i<rows;++i){
            for(int j =0;j<cols;++j){
                cout << heightMap[i][j]<< ' ';
            }
            cout << endl;
        }
#endif
        typedef tuple<int,int,int> water_x_y_tuple;//分别代表 水位高度，x,y
        vector<vector<bool>> visited(rows,vector<bool>(cols,false));
        priority_queue<water_x_y_tuple,vector<water_x_y_tuple>,comp<water_x_y_tuple>> borders;
        //initialize visited and borders
        for(int i =0;i<cols;++i){
            visited[0][i] = visited[rows-1][i] = true;
            if(i>0&& i<cols-1){
                borders.push(water_x_y_tuple(heightMap[0][i], 0, i));
                borders.push(water_x_y_tuple(heightMap[rows - 1][i], rows - 1, i));
            }
        }
        for(int i =0;i<rows;++i){
            visited[i][0] = visited[i][cols-1] = true;
            if(i>0&& i<rows-1){
                borders.push(water_x_y_tuple(heightMap[i][0], i, 0));
                borders.push(water_x_y_tuple(heightMap[i][cols - 1], i, cols - 1));
            }
        }
#ifdef DEBUG
        cout << "Top element of borders is " << get<0>(borders.top()) << endl;
#endif
        //pop shortest border, regard its value as water height. then consider 4 cells around this popped border
        //if not visited, update its height and put it into borders.
        int dirs[] = {0,1,0,-1,0}, new_x, new_y, result=0, temp;
        water_x_y_tuple shortest_border;
        while(!borders.empty()){
            shortest_border = borders.top();
            borders.pop();
            for(int i =0;i<4;++i){
                new_x = get<1>(shortest_border)+dirs[i];
                new_y = get<2>(shortest_border)+dirs[i+1];
                if(new_x >= 0 && new_x < rows && new_y >=0 && new_y < cols && !visited[new_x][new_y]){
                    visited[new_x][new_y] = true;
                    temp = max(0,get<0>(shortest_border)-heightMap[new_x][new_y]);
                    result+= temp;
#ifdef DEBUG
                    if(temp>0){
                        cout << "Current water pillar height: "<<temp<<", at (" << new_x << ',' <<new_y<<"), "
                             << "bottom height: "<<heightMap[new_x][new_y]<<", water surface height: "<<get<0>(shortest_border)
                             << ", up to now result is " << result << endl;
                    }
#endif
                    borders.push(water_x_y_tuple(max(get<0>(shortest_border), heightMap[new_x][new_y]), new_x, new_y));
                }
            }
        }
        return result;
    }
    void test(){
        vector<vector<int>> heightMap = input_helper_h::matrix(true,"407 trapping rain water2.in");
        cout << trapRainWater(heightMap);
    }
}
#endif //MAIN_CPP_407_TRAPPING_RAIN_WATER2_H
