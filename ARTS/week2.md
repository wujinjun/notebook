# ARTS-WEEK2

## Algorithm 

#### [26. 删除排序数组中的重复项](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/)

方法：快慢指针
思路：覆盖重写一个数组，慢指针来写，快指针来找

** 对比26和27题，区别在哪儿？ “排序数组”是在有序数字的后面用慢指针覆写填入不重复的数字，而“移除元素”这道题要用慢指针重新覆盖写所有数字** 

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0;
        if (nums.size() == 0) {
            return 0;
        }
        for (int fast = 0; fast < nums.size(); ++fast) {
            if (nums[fast] != nums[slow]) {
                nums[++slow] = nums[fast]; 		//注意有序数组的覆盖重写，需要++slow
            }
        }
        return slow+1;
    }
};
```

#### [80. 删除排序数组中的重复项 II](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array-ii/)

方法：快慢指针
思路：用快指针去遍历，用慢指针去覆盖写，但是引入条件“允许重复两个数字”后，需要加个计数器来操作，难点在于如何设计才能bug free

刚开始的思路是数字重复/数字不重复的两个分支处理，但是bug很多没法优雅解决；

为了优雅解决，还是需要理一下设计思路：**覆盖多余的重复项**

1. 使用快指针fast和慢指针slow，fast用来遍历， slow用来覆盖
2. 用count记录出现的次数，count初始化为1
3. 从下标1开始处理，如果nums[i] == nums[i-1]，那么count++; 如果count>2则说明遇到了相同数字，且大于2，此时只移动fast指针，slow指针不动
4. 处理完count以后，判断是否满足count<=2，如果满足则可以用slow指针来覆盖写，并将slow++；
5. 数组遍历完成后，返回直接返回慢指针slow即可 （实际上slow是个下标，由于覆盖写完后会执行slow++，因此不必返回slow+1，直接返回slow即可）

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 1;
        int count = 1;
        if(nums.size() == 0) {
            return 0;
        }

        for (int fast = 1; fast < nums.size(); ++fast) {
            if (nums[fast] == nums[fast-1]) {
                count++;
            } else {
                count = 1;
            }
            if (count <=2) {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};
```



####[277. 搜寻名人](https://leetcode-cn.com/problems/find-the-celebrity/)

方法：双指针法

思路：用给定函数knows先用排除法缩小范围到1个人；然后考察这个人是不是名人，

不是名人的考察条件是“他认识其他人” 或“其他人不认识他”

```CPP
/* The knows API is defined for you.
      bool knows(int a, int b); */


// knows(a, b)返回true说明a认识b，a不是名人；返回false说明不认识b，则b不是名人
// 如果A是名人，B代表普通人，有两个条件：A不认识B， B认识A；
// 条件空间也就只有四种：
// A->B     (A不是名人)        
// A<-B     (B不是名人)
// A<->B    (A,B都不是名人)
// A--B     (A,B都不是名人)
// knows函数返回的结果可以排除一个，可以利用它来比那里
class Solution {
public:
    int findCelebrity(int n) {
        int left = 0;
        int right = n-1;
        while(left < right) {
            if(knows(left, right)) {    // 返回true则说明left不是名人
                left++;
            } else {                    // 返回false说明right不是名人
                right--;    
            }
        }
        // 上面程序执行结束后，left==right，没有考虑left是不是名人，下面通过两个case来确认
        for (int i = 0; i < n; ++i) {
            if (i != left) {            // 和left比较的对象不能是left自己
                // case1：left认识i则说明left不是名人；
                // case2: i不认识left，说明left不是名人
                if (knows(left, i) || !knows(i, left)) {    
                    return -1;
                }
            }            
        }
        return  left;
    }
};
```



本周做的题目有三道快慢指针，贴到这里

## Review

https://www.coursera.org/learn/machine-learning/resources/JXWWS

本周准备回顾机器学习，couresera上面吴恩达的课程

准备几个问题作为检查点：

1. 描述监督学习和无监督学习之间的区别；

2. 列出并解释线性回归的假设方程和代价函数；
3. 推导并实现梯度下降在线性回归中的应用；
4. 向量的线性代数运算Review；

## Tip

Leetcode刷题按照分类来效率高一些，，死磕容易自闭；菜鸡本周最佳tips...

## Share

本周学习了编译链接，但时间有限，只手写了笔记，后续补齐后奉上链接

