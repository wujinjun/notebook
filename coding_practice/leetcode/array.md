

即日起，按照大佬整理的[leetecode分类顺序表](https://cspiration.com/leetcodeClassification)  分类刷题

### array专题

#### [27. 移除元素](https://leetcode-cn.com/problems/remove-element/)

方法：快慢指针
思路：覆盖重写一个数组，慢指针来写，快指针来找

```cpp

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        for (int fast = 0; fast < nums.size(); ++fast) {
            if(nums[fast] != val) {
                nums[slow++] = nums[fast];  //慢指针用来覆盖原数组，快指针用来寻找不等于val的值
            }
        }
        return slow;
    }
};
```

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

* 为了优雅解决，还是需要理一下设计思路
* 先处理计数器，再更新数组；

* 题目里有个明显的规律就是允许两个重复数字连续，那么就判断count <= 2的时候覆盖写数组；

* 这道题想做出来首先得理清楚思路，先干什么再干什么，上来蛮干的话bug很多；

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

方法2：

