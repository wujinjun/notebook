//
//  insert_sort.cpp
//  sort
//
//  Created by Jinjun on 2020/3/9.
//  Copyright © 2020 Jinjun. All rights reserved.
//

#include "insert_sort.hpp"
#include <iostream>

using namespace std;

void insert_sort(int arr[], int len) {
    for (int i=0; i<len; ++i) {
        int key = arr[i]; //有序区和无序区之间的标兵
        int j = i-1; //遍历游标， 从i-1向前递减遍历
        while (j >= 0 && key < arr[j]) {   //相当于抽出1个数，依次与前面的数比较
            arr[j+1] = arr[j];             //前面的数如果小于该数字就往后挪
            j--;
        }
        arr[j+1] = key;     // 循环停止时，就找到了合适的位置
    }
}
