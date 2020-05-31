# ARTS-WEEK1

## Algorithm
#### 面试题43. 1～n整数中1出现的次数
输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数。

例如，输入12，1～12这些整数中包含1 的数字有1、10、11和12，1一共出现了5次。

示例 1：
输入：n = 12
输出：5
示例 2：

输入：n = 13
输出：6


限制：

1 <= n < 2^31
注意：本题与主站 233 题相同：https://leetcode-cn.com/problems/number-of-digit-one/

**解法：** 首先排除暴力搜索，已验证会超时；这种题看起来像是DP可以做的题，但实际上并太好用DP去做, 因为不满足最优子结构条件, 而是计数为主; 以后做题遇到计数类的题目还是不要用DP了；
最后琢磨一个小时做不出来还是看了题解，看题解都费很大劲，思路各异；我选择推荐题解来理解一下，也算是做这种题目的一种思路吧！



从个位到高位逐位分析：例如 23456，分解成高位high=234  当前位cur=5  最低位low=6  位因子digit=1 (从个位往高位分析)

| dight | high | cur  | low  |
| :---: | :--: | :--: | :--: |
|   1   | 2345 |  6   |  0   |
|  10   | 234  |  5   |  6   |
|  100  |  23  |  4   |  56  |
| 1000  |  2   |  3   | 456  |

```
分析high位的影响：
		无论如何都会有234\*digit =234个1
分析cur位的影响：
		cur=0时，无影响，不加1；
		cur=1时，还要考虑low位的影响，有low+1个1（从0数到low）；
		cur>1时，考虑10，11，12，...，19 肯定要直接算上10个1；
分析low位影响：
		分析cur=1时已经覆盖该情况；

所以有三个逻辑处理分支：
1. cur==0: +high*digit
2. cur==1: +high*dight+low*1
3. cur>1： +high*dight+digit

如何迭代：
低位依赖高位！所以先处理低位再处理高位：
low = low + cur*dight;
cur = high%10
high = high/10

边界条件：
high != 0 || cur != 0  即  high == 0 && cur == 0
为什么high和cur都为0才是边界条件
只有high和cur同时为0时，才会使low覆盖到最高位

```

```cpp
class Solution {
public:
    int countDigitOne(int n) {
        long digit = 1, res = 0;
        long high = n/10, cur = n%10, low = 0;
        // 分析每位出现1的次数，依次从个位分析到高位
        // 一个数字分成三部分：高位high， 当前位cur，低位low， 位因子digit=10的x次方
        while (high != 0 || cur != 0) {  // digit从个位开始
            if (cur == 0) {
                res += high*digit;
            } else if (cur == 1) {
                res += high*digit + low + 1;    // 为什么加low? 11,12,13,14 ==> +low=4   为什么加1? 10==> +1
            } else {
                res += high * digit + digit;      // 为什么加digit？ 10,11,12,...,19,20 ==> 只有10个
            }
            low += cur * digit;
            cur = high % 10;
            high /= 10;
            digit *= 10;
        }
        return res;
    }
};
```



## Review

https://www.kdnuggets.com/2016/08/10-algorithms-machine-learning-engineers.html

这篇文章简要描述了10个算法的大致原理，适合了解概念；

但是具体地，为什么有这样的效果还需要进一步研究，

## Tip





## Share

开始



