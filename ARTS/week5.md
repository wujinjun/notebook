# ARTS-WEEK5

## Algorithm 

```
#### [243. 最短单词距离](https://leetcode-cn.com/problems/shortest-word-distance/)
方法：双指针法
思路：分别用两个指针去标记两个单词的下标；然后每出现一次就计算一次距离，并取最小值

​```cpp
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


## Share

本周进行了一些信息搜集和思考，主要是围绕着自己对未来职业发展的忧虑，我现在一家做路由器的网络设备公司，公司规模不大也不小，但我读研期间学的是通信，搞得方向是毫米波雷达，也搞了一下深度学习（主要是雷达图像识别）。

现在手上做的事情是千篇一律的重复性工作（开发测试），说是体力活也不为过，而且我认为是替别人擦屁股的活，文档不全+粗糙测试文档，我都不知道正确行为是什么样的，甚至问遍一圈人都不知道设备的正确行为是怎么样的，因为写代码的人已经离职，并且这个组件没有设计文档，只有代码，代码还有问题。

我负责的工作就是集成功能，找出bug，解决bug；还好，师傅确实会帮助我很多，避免阻塞；但我不喜欢这样擦屁股的工作，我也不喜欢数据通信这个行业...所以得考虑一下以后的发展了

看了很多视频文章，关于程序员发展的问题，最后的结论都是你得好好学习，你得努力，可是具体怎么做还是得因地制宜，每个人都有每个人的路线吧。但得找个自己喜欢的方向，回看现状，我还是比较菜的，虽然对C/C++挺熟悉，但对嵌入式不是特别熟悉，这就很尴尬，个人对物联网很感兴趣，但貌似钱不多，毕竟要赚钱买房，实现财富自由； Java那套生态是很成熟了，但是了解不多，不敢贸然下结论；安卓和IOS开发，好像热潮已经过去，不知前景如何，如果投了大把时间去做，会不会因为技术革命发生49年入GUOJUN的惨案呢？

最后的结论还是打好基础，修炼内功；技术栈变化很多，但是基础知识总是不变的；后续就继续学习加固4大件吧；

* 数据结构和算法：主要是leetcode和《剑指offer》

* 计算机网络：《TCP/IP详解》

* 操作系统：《深入理解操作系统》

* 设计模式：《大话设计模式》，几个典型：单例，工厂，代理，策略模式，模板方法

此外，还有几点实践补充：
* 编译/调试工具 GCC/Makefile/gdb
* 多线程编程/网络编程：《APUE》《Linux高性能服务器编程》《posix多线程程序设计》