//
//  main.cpp
//  sort
//
//  Created by Jinjun on 2020/3/7.
//  Copyright © 2020 Jinjun. All rights reserved.
//

#include <iostream>
#include "buble_sort.hpp"
#include "quick_sort.hpp"
#include "select_sort.hpp"
#include "insert_sort.hpp"
#include "merge_sort.hpp"
#include "heap_sort.hpp"

using namespace std;

template<typename T>
void print_arr(T arr[], int len) {
    for (int i = 0 ;i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {

    int arr[] = { 61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 62 };
    int len = (int)sizeof(arr)/sizeof(int);
//    bubble_sort(arr, len);
//    buble_sort_opt(arr, len);
//    select_sort(arr, len);
//    quick_sort(arr, len);
//    insert_sort(arr, len);
//    merge_sort(arr, len);
//    print_arr(arr, len);
    
    int arr1[] = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
    int len1 = (int) sizeof(arr1) / sizeof(*arr1);
//    merge_sort(arr1, len1);
    heap_sort(arr1, len1);
    print_arr(arr1, len1);
//
    return 0;
}
