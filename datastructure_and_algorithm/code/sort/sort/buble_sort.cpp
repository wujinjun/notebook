//
//  buble_sort.cpp
//  sort
//
//  Created by Jinjun on 2020/3/8.
//  Copyright © 2020 Jinjun. All rights reserved.
//

#include "buble_sort.hpp"

void bubble_sort(int arr[], int len) {
    int temp;

    for(int i = 0;i<len;++i) {
        for (int j = 0; j < len-1-i;++j) {
            if (arr[j+1] < arr[j]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
void buble_sort_opt(int arr[], int len) {
    int temp;
    for(int i = len-1; i >= 0; i--) {
        for (int j = 0; j < i; j++){
            if (arr[j+1] < arr[j]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
