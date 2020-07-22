# ARTS-WEEK

## Algorithm 

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




## Review


## Tip


## Share


