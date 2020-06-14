

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





####[189. 旋转数组](https://leetcode-cn.com/problems/rotate-array/)

方法：多次翻转，常用套路

1. 全部翻转
2. 前半部分翻转
3. 后半部分翻转

辅助数组的办法不满足空间复杂度为O(1)的要求，暴力解法会超时；

* 注意旋转k个长度，需要用k = k % nums.size()来优化，否则可能会重复移动导致超时

```cpp
class Solution {
public:
    void reverse(vector<int>& nums, int begin, int end) {
        int tmp;
        while(begin < end) {
            swap(nums[begin++], nums[end--]);
        }
    }

    void rotate(vector<int>& nums, int k) {
        int pre;
        int len = nums.size();
        if(len == 0) {
            return;
        }
        k = k % len;
        reverse(nums, 0, len-1);
        reverse(nums, 0, k-1);
        reverse(nums, k, len - 1);
    }
};
```





#### [41. 缺失的第一个正数](https://leetcode-cn.com/problems/first-missing-positive/)(https://leetcode-cn.com/problems/first-missing-positive/)

方法：hash，key记录正整数，val对应是否出现过；
思路：用hash来标记nums中出现过的正整数，key占位，val标记是否出现过；

* 考虑一般情况，从小到大遍历hash表，第一次出现val为0的数字就是最小的数字；

* 考虑如果n个数从1到n都在nums中这种情况，需要返回max+1；
```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int max = 0;
        for(int i = 0; i < nums.size(); ++i) {
            if (max < nums[i] && nums[i]!=INT_MAX) { //处理最大值是INT_MAX的情况
                max = nums[i];
            }
        }
        if (max <= 1) {
            return max == 1 ? 2 : 1;    //处理数组只有一个元素的情况
        }

        map<int, int> hash;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > 0) {
                hash[nums[i]] = 1;
            }
        }
        
        for (int i = 1; i < max + 1; ++i) {
            if (hash[i] == 0){
                return i;
            }
        }
        return max + 1;
    }
};
```







#### [299. 猜数字游戏](https://leetcode-cn.com/problems/bulls-and-cows/)
方法：哈希表
思路:
先处理公牛，再处理母牛；

1. 建立副本（其实可以直接用参数，但安全起见还是复制一下）分别保存为ss和sg；
2. 遍历ss和sg如果有符合公牛的情况，则公牛计数countA++, 并把公牛位置写成脏数据 ‘a’ ‘z’；
3. 同时建立hash表，记录猜过的数字和次数
4. 再次遍历ss，并以ss[i]为键在hash表中查询，如果出现过就将母牛计数countB++，同时把hash中的计数减一；
5. 最后组装答案返回

```cpp
class Solution {
public:
    string getHint(string secret, string guess) {
        unordered_map<char, int> map;
        int countA = 0, countB = 0;

        // 处理公牛，即位置和数值都相同的数字
        for(int i = 0; i < secret.length(); ++i) {
            if(secret[i] == guess [i]) {
                countA++;
                secret[i] = 'a';
                guess[i] = 'z';
            } else {
                map[guess[i]]++;   //先用hash记录猜过的每个数字的个数
            }
        }
        // 处理母牛，即数值相同但是位置不同
        for(int i = 0; i < secret.length(); ++i) {
            if (secret[i] >= '0' && secret[i] <= '9' 
                && map[secret[i]] >= 1 ) {  //检查hash表中有没有猜过的数字，有就加一，并把hash里的计数减一
                countB++;
                map[secret[i]]--;
            }
        }
        return to_string(countA) + "A" + to_string(countB) + "B";
    }
};

```