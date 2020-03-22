### 剑指Offer

[TOC]

#### 二叉树中和为某一值的路径

输入一颗二叉树的根节点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。(注意: 在返回值的list中，数组长度大的数组靠前)
* 解决思路： 
	1.搜索路径，应该想到是一个dfs问题，递归处理
	2.边界条件的考虑：路径符合题意的话需要满足
		* 结束节点是一个叶子节点，实现为代码就是node->left == NULL && node->right == NULL
		* 加上结束节点的值恰好等于期望的sum值，这里需要从根节点递归到叶子节点，每递归一个节点，sum值减去节点的val，直到减去最后的叶子节点恰好等于0，条件等价于 sum == node->val

* 递归的设计：
	1. 输入判空
	2. 先把节点记录到path数组
	3. 判断是否到达叶子节点，如果到达叶子节点，是否满足和值条件
	4. 不是叶子节点就继续递归，直到递归到叶子节点为止。
	5. 如果没有继续递归，也没有满足和值条件，那么从path数组中弹出这个节点


```cpp
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    vector<vector<int>> res;
    vector<int> path;
    void dfsFind(TreeNode* node, int sum) {
        if (node == NULL) {
            return;
        }
        path.push_back(node->val);		//path数组记录节点
      	// 判断是否为叶子节点，且满足和值条件
        if (node->left == NULL && node->right == NULL && sum == node->val) {
            res.push_back(path);
        } else {	// 不是叶子节点，继续递归
            if (node->left) {
                dfsFind(node->left, sum - node->val);
            }
            if (node->right) {
                dfsFind(node->right, sum - node->val);
            }
        }
        path.pop_back(); 	//不能被递归，也不满足和值条件，就弹出该节点
    }
    
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        dfsFind(root, expectNumber);
        return res;
    }
};

```



