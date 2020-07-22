
//
//  heap_sort.cpp
//  sort
//
//  Created by Jinjun on 2020/3/10.
//  Copyright © 2020 Jinjun. All rights reserved.
//

#include "heap_sort.hpp"
#include <iostream>

using namespace std;
//下沉堆化操作有些难以理解
//k是堆的元素个数，i是堆化的对象
static void sink1(int a[], int len, int i) {
    while(true) {
        int maxpos = i; //堆化操作的开始节点,用下标的方式寻找最大
        if(2*i+1 < len && a[i] < a[2*i+1]) maxpos = 2*i+1;        //和左子节点比较
        if(2*i+2 < len && a[maxpos] < a[2*i+2]) maxpos = 2*i+2;   //和右子节点比较
        if(maxpos == i) break;
        swap(a[i], a[maxpos]);
        i = maxpos;
    }
}
//比较好理解一些，先比较两个子节点的大小，再和父节点比较，相较于sink1少了一个中间变量
static void sink2(int a[], int len, int i) {
    while(2*i+1 <= len) {
        int son = 2*i+1;      //j是左子节点的下标
        if(son < len && a[son] < a[son+1]) son++; //优选较大的子节点，左子节点比右子节点小
        if(a[i] > a[son]) break;  //目标节点a[i]比两个子节点都大，直接返回
        swap(a[i], a[son]);
        i = son;
    }
}
//初始化大顶堆
static void build_heap(int *arr, int k, int len) {
    //最后一个非叶子节点的下标怎么计算的？是一个证明题，暂且记住是len/2 - 1 (下标从0开始)    len/2 (下标从1开始)
    for(int i = len/2 - 1; i >= 0; i--) {
        sink2(arr, k, i);
    }
}

//下标i从0开始， 左子节点下标为2i+1，右子节点下标为2i+2，父亲节点下标为(i-1)/2
void heap_sort(int arr[], int len) {
    int k = len-1;
    //初始化大顶堆
    build_heap(arr, k, len);
    //弹出堆顶元素，并堆化
    for(int i = len - 1; i >= 0; i--) {
        swap(arr[0],arr[k]); //堆顶和最后一个元素进行交换
        k--;    //移除最大元素
        sink2(arr, k, 0);   //对堆顶进行一次下沉堆化操作
    }
}


