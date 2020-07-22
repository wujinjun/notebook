
//
//  merge_sort.cpp
//  sort
//
//  Created by Jinjun on 2020/3/10.
//  Copyright © 2020 Jinjun. All rights reserved.
//

#include "merge_sort.hpp"

void merge(int arr[], int aux[], int lo, int mid, int hi) {
    
    int k = lo;
    int start1 = lo, end1 = mid, start2 = mid+1, end2 = hi;
    while(start1 <= end1 && start2 <= end2) {
        if (arr[start1] < arr[start2]) {
            aux[k++] = arr[start1++];
        } else {
            aux[k++] = arr[start2++];
        }
    }
    while (start1 <= end1) {
        aux[k++] = arr[start1++];
    }
    while (start2 <= end2) {
        aux[k++] = arr[start2++];
    }

    for (int k = lo; k <= hi;k++) {
        arr[k] = aux[k];
    }
    
}

void sort(int arr[], int aux[], int lo, int hi) {
    //终止条件
    if (lo >= hi) {
        return;
    }
    int mid = ((hi-lo)>>1) + lo;
    sort(arr, aux, lo, mid);
    sort(arr, aux, mid+1, hi);
    merge(arr, aux, lo, mid, hi);
}

void merge_sort(int arr[], int len){
    int aux[len];
    sort(arr, aux, 0, len-1);
}

