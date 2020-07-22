//
//  select_sort.cpp
//  sort
//
//  Created by Jinjun on 2020/3/8.
//  Copyright © 2020 Jinjun. All rights reserved.
//

#include "select_sort.hpp"
#include <iostream>

using namespace std;

void select_sort(int arr[], int len) {
    for(int i = 0; i < len;++i) {
        int min_index = i;
        for(int j = i+1; j<len;++j) { //遍历查找一个最小的数，找到记录下标
            if(arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        swap(arr[i],arr[min_index]);  //把最小的数字和arr[i]交换
    }
}
