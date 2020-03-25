## 排序

### 1. 冒泡排序

```cpp
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
```

### 2. 选择排序
```cpp
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
```

### 3.快速排序
```CPP
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
```

### 4. 插入排序
```cpp
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
```

### 5.归并排序
```cpp
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
```

## TODO:
#### 6. 堆排序

