//
//  quick_sort.cpp
//  sort
//
//  Created by Jinjun on 2020/3/8.
//  Copyright © 2020 Jinjun. All rights reserved.
//

#include "quick_sort.hpp"
#include <iostream>

using namespace std;

//返回的是切分值的坐标，目的就是把小的数丢到左边，大的数丢到右边，然后为pivot找个位置并返回坐标
int quick_partial(int arr[], int low, int high){
    int pivot = arr[low];
    int i = low;        //为了循环中++i操作后，得到arr[i] = arr[low+1]
    int j = high+1;     //为了循环中--j操作后，得到arr[j] = arr[high]
    while(1) {
        while(pivot >= arr[++i] && i != high);
        while(pivot <= arr[--j] && j != low);
        if (i >= j) break;  //循环结束后一定是 i > j
        swap(arr[i],arr[j]);
    }
    swap(arr[low],arr[j]);  //这个地方非常细节，为什么要arr[j]和arr[low]交换？
                            //原因是经过循环里的--j操作后，arr[j]右边的数组都比pivot大，arr[j]左边的数字逗比pivot小
    return j;       // j 对应的位置就是pivot, 此时的arr[j] == pivot
}


void quick_sort(int arr[], int low, int high) {
    if (low >= high) {
        return;
    }
    int mid = quick_partial(arr, low, high);
    quick_sort(arr, low, mid-1);
    quick_sort(arr, mid+1, high);
}

void quick_sort(int arr[], int len){
    quick_sort(arr,0,len-1);
}
