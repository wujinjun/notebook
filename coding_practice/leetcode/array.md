

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

#### [134. 加油站](https://leetcode-cn.com/problems/gas-station/)

方法：贪心

思路：逐个遍历排除，由于循环对称性，只需要从下标0开始遍历就可以

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int remain = 0;
        int total = 0;
        int station = 0;
        for (int i = 0; i < n; i++) {
            total += gas[i] - cost[i];	//计算所有加油站加的油减去所有路上消耗的油，用来判断是否返回-1；
            remain += gas[i] - cost [i];	//计算每次走一段路，油箱余量油==加的油减去消耗的油
            if (remain < 0) {		//如果油箱余量油小于0，那么这个加油站肯定不是起点
                station = i+1;	//考察下一个加油站
                remain = 0;     //清空油箱
            }
        }
        return total >= 0 ? station : -1;
    }
};
```

#### [274. H 指数](https://leetcode-cn.com/problems/h-index/)

方法：哈希表法

思路：暴力法O(N^2)复杂度，建立一个哈希表，用来记录引用1，2，...， N次的文章总共有几篇；

```cpp
class Solution {
public:
    //用一个哈希表记录
    int hIndex(vector<int>& citations) {
        unordered_map<int,int> hash;//用来记录引用0，1，..., n次的论文有几篇
        int res = 0;
        for (int i = 0; i < citations.size(); ++i) {
            for (int j = 1;j <= citations[i]; ++j) {
                hash[j]++;
                if(hash[j] == j) {
                    res = j;
                }
            }            
        }
        return res;
    }
};
```

#### [175. H指数 II](https://leetcode-cn.com/problems/h-index-ii/)
方法:  二分查找
思路：二分查找的复杂度为O(logN); 该题的关键是想出来什么情况下该向右搜索，什么情况下该向左搜索； 思考的捷径就是考虑一些比较极端的例子，如[1,1,1,1,2,3]就会非常形象地确认边界条件；
papercount = len - mid 论文数量
* 引用次数 < 论文数量:    cit[i] < papercount，应该向右搜索
* 引用次数 > 论文数量:  cit[i] > papercount，应该向左搜索
* 返回值就是论文的h值，此时跳出while循环后 low == high； 返回值为 len - low == len -high；
* 需要注意的是，需要处理输入的特殊情况，[] 或[0]这种输入；
```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        if(citations.size() == 0 || citations.back() == 0) return 0; 
        int low = 0; 
        int high = citations.size()-1, len = citations.size();
        int mid = 0;
        while (low < high) {
            int mid = low + (high - low)/2;
            int papercount = len - mid; //统计论文数量
            if (citations[mid] < papercount) {  //向右搜索, 形象的例子[1,1,1,1,2,3]
                low = mid + 1; 
            } else if(citations[mid] > papercount){     //向左搜索, 形象的例子[5,6,7,8,9]
                high = mid;
            } else {
                return len - mid;
            }
        }
        return len - low;
    }
};
```
#### [243. 最短单词距离](https://leetcode-cn.com/problems/shortest-word-distance/)
方法：双指针法
思路：分别用两个指针去标记两个单词的下标；然后每出现一次就计算一次距离，并取最小值

```cpp
class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int pos1 = -1;
        int pos2 = -1;
        int res = INT_MAX;
        for (int i = 0; i < words.size();++i) {
            if (words[i].compare(word1) == 0){
                pos1 = i;
            } else if (words[i].compare(word2) == 0) {
                pos2 = i;
            }
            if (pos1 != -1 && pos2 != -1 && abs(pos2 - pos1) < res) {
                res = abs(pos2 - pos1);
            }
        }
        return res;
    }
};
```

#### [244. 最短单词距离 II](https://leetcode-cn.com/problems/shortest-word-distance-ii/)
方法： 哈希+双指针法
思路：用哈希存下来所有单词出现的下标，用vector存，然后用双指针分别在两个数组里取值、作差比较，直到得到最小值res为止；


```cpp
class WordDistance {
public:
    unordered_map<string, vector<int>> hash;
    WordDistance(vector<string>& words) {
        for (int i = 0; i < words.size();++i) {
            hash[words[i]].push_back(i);    //key是单词， value是单词出现的下标,用vector存起来
        }
    }
    
    int shortest(string word1, string word2) {
        int res = INT_MAX;
        //从hash中取出对应单词的vector
        vector<int> &vec1  = hash[word1];   //从hash中取出对应单词的vector
        vector<int> &vec2  = hash[word2];
        //双指针法作差比较，指针都初始化为0；
        int pos1 = 0;
        int pos2 = 0;
        while (pos1 < vec1.size() && pos2 < vec2.size()) {
            // 选择"res"和"差值"中较小的作为res;
            res = min(res, abs(vec2[pos2] - vec1[pos1]));
            //指针的移动处理，将取值较小的指针+1
            if (vec1[pos1] < vec2[pos2]) {                
                ++pos1;
            } else {
                ++pos2;
            }
        }
        return res;
    }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(words);
 * int param_1 = obj->shortest(word1,word2);
 */
```



#### [217. 存在重复元素](https://leetcode-cn.com/problems/contains-duplicate/)

方法：哈希，set

思路：

哈希法，value用来计数出现的次数

set法，相当于去重，比较容器size，不相等则说明有重复的元素

```cpp
// set法
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        return nums.size() > set<int>(nums.begin(), nums.end()).size();
        
    }
};

//哈希表法
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,int> map;
        for (int i = 0; i < nums.size(); ++i) {
            map[nums[i]]++;
            if (map[nums[i]] > 1) {
                return true;
            }
        }
        return false;
    }
};


```



#### [55. 跳跃游戏](https://leetcode-cn.com/problems/jump-game/)

方法： 贪心

思路： 这道题的解题点在于“从每个下标出发，能到达的最远距离是否达到了最后的位置”
核心代码就一行
`max_dis = max(max_dis, i + nums[i]);`; 就是更新max_dis，游戏开始的时候初始化为`max_dis = nums[0];`



```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
         int len = nums.size();
         if (len <= 1) return true;

         int max_dis = nums[0];
         //输入: [3,2,1,0,4]
         for (int i = 1 ; i < len; ++i) {
             if (i <= max_dis) {
                 //下标为i的位置最远能到的距离就是:i目前的位置 + 从i开始可跳出的最远距离
                 max_dis = max(max_dis, i + nums[i]);    
             }
         }
        return max_dis >= len - 1;
    }
};
```



#### [45. 跳跃游戏 II](https://leetcode-cn.com/problems/jump-game-ii/)

方法： 贪心

思路： 首先不可否认的是这道题的贪心还是比较取巧的，是跳跃游戏的加强版；

基本的思路就是在每次跳跃时，都跳到最远的地方；这样的话，跳跃的次数就最少。

* 实际上从下标0开始跳，所以起跳地点jump_idx初始化为0；
* for循环开始考察每个下标能够跳到的最远距离：`max_pos = max(max_pos, nums[i]+ i);`
* for循环里考察到起跳地点时`i == jump_idx`：
  * 把当前能跳到的最远距离`max_pos`作为新的起跳地点`jump_idx = max_pos`;
  * 跳跃次数加一`++steps;`
  * 边界条件：如果起跳地点到达终点或者超出终点`jump_idx >= len-1`，则说明已经得到了最终结果，打断循环返回steps即可

```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        int steps = 0;
        int jump_idx = 0;   //用来记录再次起跳的位置
        int max_pos = 0;
        int len = nums.size();
        //不用考虑从最后一个位置起跳的情况，所以i < nums.size()-1，而不是i < nums.size()
        for (int i = 0; i < len-1; ++i){ 
            max_pos = max(max_pos, nums[i]+ i);
            // 会不会一直迭代下去？什么时候停止++steps？
            // 隐藏的边界条件，i < len - 1 ==> jump_idx < len - 1; 所以jump_idx超出len - 1以后，结果就定下来了
            if (i == jump_idx) {        //i到达起跳位置
                jump_idx = max_pos;     //下次起跳位置设置为本次贪心计算得到的最远距离处
                ++steps;
                if (jump_idx >= len-1) {    //优化：起跳点达到或者超过终点就可以结束循环了
                    break;
                }
            }
        }
        return steps;
    }
};
```

#### [121. 买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)

方法： 暴力法，已经超时，不用考虑了

方法：贪心

思路：先设置一个max_profit和一个min_price; 然后一次遍历更新就可以求解；

具体地，先遍历一遍，得出哪天的股票价格最低，在实现中也就是遍历时通过`min_price = min(min_price, prices[i]); `动态更新最低价格

然后在随后的每一天都去计算，如果以最低价格min_price买入了股票，今天卖出去能否赚最多，在实现中也就是遍历过程中通过`max_profit = max(max_profit, prices[i] - min_price);` 动态更新最高收益；

```CPP
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min_price = INT_MAX;
        int max_profit = 0;
        for (int i = 0; i < prices.size();++i) {
            max_profit =  max(max_profit, prices[i] - min_price);
            min_price = min(min_price, prices[i]);
        }

        return max_profit;
    }
};
```



#### [122. 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)

方法： 贪心

思路：首先不要被买入和卖出的字眼所迷惑，我们要做的就是利益最大化，做题的时候可以考虑局部最优，先别考虑全局最优否则太发散，于是我们关注第一天买入，第二天就卖出的情况，看起来是局部最优；实际上已经是全局最优了，如果每次在股票涨价之前你都买入，涨价后卖出，那么就是局部最优叠加出来的全局最优，因为你不会亏钱，你已经知道第二天的股价是跌是涨了；

考虑： 从第二天开始考察， 如果今天卖了可以赚钱，那么就假设昨天已经买了，今天卖出就赚钱了；

实现的时候只要`tmp = prices[i] - prices[i-1];` 大于0就累加起来作为收益

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        int tmp = 0;
        for (int i = 1; i < prices.size(); ++i) {
            tmp = prices[i] - prices[i-1];
            if (tmp > 0) res = res + tmp;
        }
        return res;
    }
};
```



方法：动态规划

思路：DP的精髓就在分析出有几种状态，状态如何转移

首先确定有两个状态 {持有现金，持有股票}，这意味着每天不论怎么操作（继续持有现金或股票，买入或卖出股票）都会确定到两个状态；

**状态转移分析：**

(1) 不做操作==》持有现金 状态C

(2) 卖出股票==》持有现金 状态C

(3) 不做操作==》持有股票 状态S

(4) 买入股票==》持有股票 状态S

对于(1)和(2)，第i天的现金利润`cash_profit[i] = max{(无股票不操作时持有的现金利润),（卖出股票得到的现金利润）}  `

对于(3)和(4)，第i天的现金利润`stock_profit[i] = max{(有股票不操作时持有的现金利润), (花现金买入股票剩余现金利润)}`

于是，状态转移方程就出来了，第一行归纳状态转移  C-->C  和  S-->C；第二行归纳S-->S和C-->S

**边界状态：**

`profit_cash[0] = 0;            // 第一天持有现金，则获利为0`
`profit_stock[0] = -prices[0];  // 第一天持有股票，则获利为负数`

 代码如下：

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        if (n<=1) {
            return 0;
        }
        int profit_cash[n];
        int profit_stock[n];
        
        // cash表示持有现金的状态，数额表示获利情况
        // hold表示持有股票的状态，数额表示获利情况
        profit_cash[0] = 0;            // 第一天持有现金，则获利为0
        profit_stock[0] = -prices[0];  // 第一天持有股票，则获利为负数

        for(int i = 1; i < prices.size(); ++i) {
            // cash->cash   stock->cash
            profit_cash[i] = max(profit_cash[i-1], profit_stock[i-1] + prices[i]);  //要么继续持有现金，要么卖出一笔股票得到现金
            // stock->stock   cash->stock
            profit_stock[i] = max(profit_stock[i-1], profit_cash[i-1] - prices[i]); //要么继续持有股票，要么花费一定现金得到一笔股票
        }
        return profit_cash[n-1];
    }
};

```

