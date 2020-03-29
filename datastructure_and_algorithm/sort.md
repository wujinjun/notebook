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

### 6. 堆排序
[堆](heap.md)的数据结构和特性

#### 堆排序（假设需要从小到大的堆排序）

思路1：先初始化大顶堆，然后循环==>(删除堆顶元素+堆化收敛)，直到堆空为止
* 初始化堆：将数组看成一个堆的结构，从后往前遍历非叶子节点，对每个叶子节点做下沉操作
* 删除堆顶元素：把堆顶元素与最后一个元素进行交换，再把数组临时长度N-1，后面数字就是有序的
* 堆化收敛：对执行一次下沉操作，即可保持堆的有序化

```cpp
//下沉堆化操作有些难以理解
//k是堆的元素个数，i是堆化的对象
void sink1(int a[], int len, int i) {
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
void sink2(int a[], int len, int i) {
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
```
