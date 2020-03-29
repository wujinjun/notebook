# Leetcode note

[TOC]

### 1. 两数之和

https://leetcode.com/problems/two-sum/

解法1: 暴力搜索法

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        for(int i=0;i<nums.size();++i) 
        {
            for(int j=i+1;j<nums.size();++j)
            {
                if(target==nums[i]+nums[j])
                {
                    res.push_back(i);
                    res.push_back(j);
                    break;
                }
            }
        }
        return res;
    }
};
```
- 解法2：两遍哈希表
1. 第一遍哈希表，key作为数组值，value作为数组下标
2. 第二遍哈希表，根据目标做减法，减法所得值在哈希表中查询O(1)，如果有就返回 两个下标（减法结果值下标，轮询值下标）

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        unordered_map<int, int> hash;
        int oth = 0;
        for(int i = 0;i < nums.size();++i)
        {
            hash[nums[i]] = i;                      //hash的key是数组元素，value是下标
        }
        for(int i = 0;i < nums.size();++i)
        {
            oth = target - nums[i];                 //目标值减去迭代值，得到第2个数，再检查第2个数是否在数组中
            if(hash.count(oth) && hash[oth] != i)   //检索第2个数是否在hash表中，并且如果存在还需要保证不是迭代值本身
            {
                res.push_back(hash[oth]);           //如果存在第2个数，先把e第二个数的下边push进去
                res.push_back(i);                   //再把迭代值的下标push进去
                return res;
            }
        }
        return res;
    }
};

```



### 7. 整数翻转
- 存储每个位的数字
- 依次fanzhuan
- 检查是否溢出
```cpp
class Solution {
public:
    int reverse(int x) {
        
        long bcount = 1;
        long y = 0;
        vector<int> cache;
        
        //依次存储各个位置上的数字
        while(x) {
            cache.push_back(x%10);  
            x /= 10;
            bcount *= 10;   //注意，有几位数字，bcount就有几个0
        }        
        
        // 依次将数字乘以位数后翻转
        bcount = bcount/10;
        for(int i=0;i<cache.size();++i) {
            y = y+cache[i]*bcount;
            bcount = bcount/10;
        }
        // 检查是否溢出
        if(y > INT_MAX || y < INT_MIN) {
            return 0;
        }
        
        return y;
    }
};
```

### 9. 回文数判断

实际上是利用数学归纳法来做
例如输入3571，需要对比1753，那怎么构造呢？
1 = 1
17 = 10 + 7
175 = 170 + 5
1753 = 1750 + 3

```
class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) {
            return false;
        }

        long num = 0;
        int tempx = x;
        
        while(x) {
            num = num*10 + x%10;
            x /=10;
        }
        return num == tempx;
    }
};

```

### 13. 罗马数字转整数

```
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

```cpp
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> map;
        map['I'] = 1;
        map['V'] = 5;
        map['X'] = 10;
        map['L'] = 50;
        map['C'] = 100;
        map['D'] = 500;
        map['M'] = 1000;
        
        int res = 0;
        for(int i = 0; i != s.length(); ++i)
        {
            if(s[i] == 'I' && (s[i+1] == 'V' || s[i+1] == 'X')) {
                if(s[i+1] == 'V')res += 4;
                if(s[i+1] == 'X')res += 9;
                i++;
                continue;
            }
            if(s[i] == 'X' && (s[i+1] == 'L'||s[i+1] == 'C')) {
                if(s[i+1] == 'L')res += 40;
                if(s[i+1] == 'C')res += 90;
                i++;
                continue;
            }
            if(s[i] == 'C' && (s[i+1] == 'D'||s[i+1] == 'M')) {
                if(s[i+1] == 'D')res += 400;
                if(s[i+1] == 'M')res += 900;
                i++;
                continue;
            }
            res += map[s[i]];
        }
        return res;
    }
};
```
### 24. 两两交换链表中的数字

分别有两种解法，迭代和递归

迭代：4个指针来操作，pre, p1, p2, cur,
1. pre用来衔接前驱，p1和p2用来交换操作，cur用来走读链表
2. 首先需要稳妥地把head保存为head->next, 初始化的时候就得做了，在循环里是不太好操作的
3. 然后 `p1=cur,p2 = p1->next`先保存两个节点，然后交换他们`p1->next = p2->next;p2->next = p1;` 这个没什么难的
4. 关键是前面的节点和后面的节点怎么维护呢？实际上后面的节点`p1->next = p2->next`就搞定了，但是对于前面的节点而言，需要先让它指向p2：`pre->next = p2`，然后再让前面的几点`pre=p1`
5. 为什么要让前面的节点这样做呢？p1和p2交换了位置，所以pre必须指向p2；而p1指向的又是后面两个新的可迭代处理的节点，所以需要pre当然是后面两个节点的pre；


```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head == NULL || head->next == NULL) {
            return head;
        }
        ListNode *cur = head;
        ListNode *pre = NULL;
        head = head->next;
        while (cur && cur->next) {  //需要处理所有节点，但要判断第一个和第二个节点
            ListNode *p1 = cur;
            ListNode *p2 = p1->next;
            
            if (pre != NULL) {
                pre->next = p2;
            }
            p1->next = p2->next;    //交换
            p2->next = p1;          //交换
            cur = p1->next;         //继续走读
            pre = p1;
        return head;
    }
};

```

### 26. Remove Duplicates from Sorted Array

https://leetcode.com/problems/remove-duplicates-from-sorted-array/

解法1:  双指针法

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size()==0)
            return 0;
        int i = 0;
        for(int j=1;j<nums.size();++j)
        {
            if(nums[j]!=nums[i])
                i++;
                nums[i] = nums[j];
        } 
        return i+1;
    }
};
```

解法2: std:unique删除重复元素

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        nums.erase(std::unique(nums.begin(), nums.end()),nums.end());
        return nums.size();
    }
};
```



### 27. Remove Element

Resolution 1: 双指针法

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int i=0;
        for(int j=0; j<nums.size();++j)
        {
            if(nums[j]!=val)
            {
                nums[i]=nums[j];
                i++;
            }
        }
        return i;
    }
};
```

Resolution 2:  （std::distance + std::remove ） 

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
            return std::distance(nums.begin(), std::remove(nums.begin(), nums.end(), val));
    }
};
```

Resolution 2:   （std::vector::erase + std::remove） 

```cpp
class Solution { 
public:
    int removeElement(vector<int>& nums, int val) {
            nums.erase(std::remove(nums.begin(),nums.end(),val), nums.end());
            return nums.size();
    }
};
```



### 35. 搜索插入位置

二分查找，但是边界条件需要非常仔细地考虑清楚
```cpp

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if(nums.empty()){
            return 0;
        }
        int left = 0;
        int right = nums.size()-1;
        int mid;
        while(left < right){
            
            mid = left+(right-left)/2;
            if(nums[mid] == target) {
                return mid;
            }
            if(nums[mid]>target) {
                right = mid-1;
            }
            if(nums[mid]<target) {
                left = mid+1;
            }
        }
        if(nums[left]<target) {
            return left+1;
        }
        return left;
        
    }
};

```


### 141. 环形链表
快慢指针还是不错的

1. 判断依据是快指针和慢指针
2.然后让快慢指针后移，快指针后移两个，慢指针后移一个，不过移动之前需要检查条件，免得指针指空，但是如果指针可以指空那就说明没有环

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == NULL) {
            return false;
        }
        ListNode *p1=head, *p2=head->next;
        while(p1 && p2) {
            if (p1 == p2) {     //判断是否有环
                return true;
            }
            if (p1->next && p2->next && p2->next->next) { //判断是否可以后移
                p1 = p1->next;
                p2 = p2->next->next;
            }
            else {
                return false;
            }
        }
        return false;
    }
};

```

### 206. 链表反转

反转链表需要使用三个临时变量来解决

```cpp
//初始化：
prev = NULL；   //操作节点的前驱
cur = head；    //操作节点
tmp = NULL；    //操作节点的后继
循环体：
tmp = cur->next     //第一步先保存后边未操作的链表，因为要对cur->next动手脚，所以先保存下来
cur->next = prev    //第二步就是将当前节点从“向后指”改变为“向前指”；
prev = cur          //第三步prev指针后移
cur = tmp           //第四步cur指针后移
```

处理思路的**关注点是将`cur->next`指向`prev`**，也就是第二步。但是需要考虑一下几点：

- 考虑链表丢失的问题先存个tmp = cur->next；
- 考虑需要依次处理整个链表，所以prev和tmp节点都需要往后滑动
- 考虑循环结束时候的边界条件，注意是cur—>next = prev这一步ok以后才算大功告成，

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *cur, *prev, *tmp;
        prev = NULL;
        cur = head;
        while(tmp) {
            tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }
        
        return prev;
    }
};
```


### 