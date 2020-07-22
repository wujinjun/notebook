# ARTS-WEEK6

## Algorithm 

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




## Share: 操作系统的异常



操作系统在正常工作时，会平滑地执行一个指令序列，但有时候不得不处理突如其来的一些事情，比如相应定时器中断，硬件中断，进程间的信号通信以及非本地跳转等都可以被称为异常控制流

### 1.1 异常

异常是控制流里的突变。程序A在执行过程中，如果发生异常，控制权将暂时交给异常处理程序B，等异常处理程序B执行完成后，可能会有3种情况：

* 将控制权返还给程序A，再次执行发生异常时正在执行的指令$I_{cur}$
* 将控制权返还给程序A，执行下一条指令$I_{next}$
* 异常处理程序终止程序A

### 1.2 异常处理

* 异常表是操作系统分配和初始化的一个跳转表，作用是根据不同的异常号跳转到不同的异常处理程序
* 异常处理程序运行在内核模式下，对所有的系统资源都有访问权限

### 1.3 异常的类别

* 中断：异步发生，是来自处理器外部的I/O设备的信号触发的，返回后执行下一条指令
* 陷阱：同步发生，系统调用出发，从用户态陷入内核态进行处理，返回后执行下一条指令
* 故障：同步发生，由错误引起，可能会被故障处理程序修正，再次执行原来的指令；也有可能无法修正，故障处理程序将控制交给内核的abort例程，终止原来的程序；经典的故障就是“缺页”异常
* 终止：同步发生，是不可恢复的致命错误导致的，通常是一些硬件错误，如DRAM或SRAM被损坏，终止处理程序直接将控制交给内核的abort例程，然后终止原来的程序。

### 1.4 x86-64系统中的异常

x86-64系统有256种不同的异常，异常号0-31对应的是Intel架构师定义的异常，所有x86-64系统都一样，异常号32-255对应操作系统定义的中断和陷阱。

**典型的故障**

1. **除法错误**，也称为浮点异常，当程序试图除以0就会发生该错误
2. **一般性保护故障** ，也称为段错误，一般是因为引用了未定义的内存地址，或试图写一个只读的文本段；
3. **缺页**，发生该错误时，说明虚拟地址没有在页表命中对应的PTE，根据页表去磁盘中读对应的页，并加载到物理内存中，然后用页表建立虚拟内存和物理内存之间的映射关系。