### 剑指Offer

[TOC]



#### 反转链表
输入一个链表，反转链表后，输出新链表的表头
```cpp
/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        ListNode *pre, *next,*cur;
        pre = NULL;
        cur = pHead;
        next = NULL;
        while (cur != NULL) {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};
```


#### 树的子结构

输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）

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
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        bool res = false;
        if(pRoot1 != NULL && pRoot2 != NULL) {
            if(pRoot1->val == pRoot2->val) {
                res = isSubtree(pRoot1,pRoot2);
            }
            if(!res) {
                res = HasSubtree(pRoot1->left, pRoot2);
            }
            if(!res) {
                res = HasSubtree(pRoot1->right, pRoot2);
            }
        }
        return res;
    }
    bool isSubtree(TreeNode *p1, TreeNode* p2) {
        if (p2 == NULL) {
            return true;
        }
        if (p1 == NULL) {
            return false;
        }
        if(p1->val != p2->val){
            return false;
        } 
        return isSubtree(p1->left, p2->left) && isSubtree(p1->right, p2->right);
    }
};
```

#### 二叉树的镜像
操作给定的二叉树，将其变换为源二叉树的镜像。
输入描述:
二叉树的镜像定义：源二叉树 
    	    8
    	   /  \
    	  6   10
    	 / \  / \
    	5  7 9 11
    	镜像二叉树
    	    8
    	   /  \
    	  10   6
    	 / \  / \
    	11 9 7  5
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
    void Mirror(TreeNode *pRoot) {
        if (pRoot == NULL) {
            return;
        }
        TreeNode *pTemp = pRoot->right;
        pRoot->right = pRoot->left;
        pRoot->left = pTemp;
        if (pRoot->left) {
            Mirror(pRoot->left);
        }
        if (pRoot->right) {
            Mirror(pRoot->right);
        }
        return;
    }
};
```

#### 顺时针打印矩阵
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下4 X 4矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.

```cpp
class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<vector<int> > copy(matrix);
        vector<int> res;
        while(copy.size() != 0 && copy[0].size() !=0) {
            for (int i = 0; i < copy[0].size(); ++i) {
                res.push_back(copy[0][i]);
            }
            copy.erase(copy.cbegin());
            if(copy.size() != 0 && copy[0].size() != 0)
                copy = rotate(copy);
            }
        return res;
    }
    vector<vector<int>> rotate(vector<vector<int> > matrix) {
        vector <vector<int> > res(matrix[0].size(), vector<int> (matrix.size()));
        int m = 0;
        int n = 0;
        for (int i = matrix[0].size() - 1; i >= 0; --i) {
            for (int j = 0; j < matrix.size(); ++j) {
                res[m][n++] = matrix[j][i];
            }
            m++;
            n = 0;
        }
        return res;
    }
};
```

#### 包含min函数的栈
定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的min函数（时间复杂度应为O（1））。
注意：保证测试中不会当栈为空的时候，对栈调用pop()或者min()或者top()方法。
```cpp
class Solution {
public:
    void push(int value) {
        s.push(value);
        if(s_min.empty() || value < s_min.top())
            s_min.push(value);
    }
    void pop() {
        if (s_min.top() == s.top()) 
            s_min.pop(); 
        s.pop();
    }
    int top() {
        return s.top();
    }
    int min() {
        return s_min.top();
        
    }
private:
    stack <int> s;
    stack <int> s_min;

};
```

#### 栈的压入、弹出序列
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）
```cpp
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        //压入一个，尝试弹出一次，如果最后能够全部弹出，就说明是弹出序列
        stack<int> s;
        for (int i = 0, j = 0; i < pushV.size(); ++i) {
            s.push(pushV[i]);
            while( j < popV.size() && popV[j] == s.top()) {     //j < popV.size()  为什么？？？===》
                s.pop();
                j++;
            }
        }
        return s.empty();
    }
};
```

#### 从上往下打印出二叉树的每个节点，同层节点从左至右打印。
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
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        queue<TreeNode*> line;
        vector<int> res;
        if (root == NULL) {
            return res;
        }
        TreeNode *p;
        line.push(root);
        while(!line.empty()) {
            p = line.front();
            res.push_back(p->val);
            if (p->left != NULL) {
                line.push(p->left);
            }
            if (p->right != NULL) {
                line.push(p->right);
            }
            line.pop();
        }
        return res;
            
    }
};
```

####  二叉搜索树的后序遍历序列

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。

```cpp
class Solution {
public:
    bool IsBST(vector<int> &a, int start, int end) {
        // 结构：  左子树+右子树+根节点
        if (start >= end) {                //该条件说明数组遍历结束，符合有序
            return true;
        }
        int pivot;
        for(pivot = end; a[--pivot] > a[end];);  // 寻找切分点，从后往前寻找
        for(int i = pivot; i >= 0; i--) {        // 检查前半段数字是否都是符合小于根节点
            if(a[i] > a[end]) return false;
        }
        return IsBST(a, start, pivot) && IsBST(a, pivot+1, end-1);    //分治递归检查
        
    }
    bool VerifySquenceOfBST(vector<int> sequence) {
        if(sequence.size()==0) return false;
        return IsBST(sequence, 0, sequence.size()-1);
    }
    
};
```



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



#### 复杂链表的复制

输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）

```cpp
/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
/*
首先想到的办法是直接遍历一遍，把指针关系记录下来，复制的时候再把指针关系恢复上去；
但是指针的指向关系是原始链表的指向关系，复制到新链表的话还是指向原始链表；
解决方法1：
1.遍历第一遍，在原始链表的每个节点后面插入一个新的节点
2.遍历第二遍，用random指针来遍历，将每个节点的后继节点的random指向本节点random节点的next；
    实际上是通过跟踪旧链表random的指向来更新新链表的random指针
3.拆分链表，其实就是依次更新原链表和新链表的next指针，然后再迭代遍历链表；注意边界条件，不要访问到空指针
*/
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if (!pHead) return NULL;
        RandomListNode *cur = pHead;
        //1.第一次更新，复制节点
        while (cur) {
            RandomListNode *node = new RandomListNode(cur->label);
            node->next = cur->next;
            cur->next = node;
            cur = node->next;
        }
        //2.第二次遍历，更新random指针
        cur = pHead;
        while (cur) {
            RandomListNode *node = cur->next;
            if(cur->random) {
                node->random = cur->random->next;
            }
            cur = node->next;
        }
        //3. 第三次遍历，拆分链表
        //拆分步骤需要思考：其实就是依次更新原链表和新链表的next指针，然后再迭代遍历链表
        RandomListNode *newhead = pHead->next;
        RandomListNode *newcur =  newhead;
        cur = pHead;
        while (cur) {
            cur->next = cur->next->next;
            if(newcur->next)    //最后一次循环的边界条件，避免访问空指针
                newcur->next = newcur->next->next;
            cur = cur->next;
            newcur = newcur->next;
        }
        return newhead;
    }
};
```

二叉搜索树与双向链表

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。

解决思路： 最后返回一个排序的双向链表，因此：

1. 先对二叉树进行中序遍历，把中序遍历的结果存储到一个数组中，
2. 依次从数组中取出二叉树的节点串成双向链表

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
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        if(pRootOfTree == NULL) {
            return NULL;
        }
        vector<TreeNode *> list;
        Convert(pRootOfTree, list);		//中序遍历，并把节点存储到数组中
        return ProcessList(list);			//把数组中的节点处理成双向链表
    }
    
    void Convert(TreeNode* p, vector<TreeNode *> &list) {
        if(p != NULL) {
            Convert(p->left,list);
            list.push_back(p);
            Convert(p->right,list);
        }
        
    }
    TreeNode* ProcessList(vector<TreeNode *> list) {
        TreeNode * head = list[0];
        TreeNode * cur = head;
        for(int i=1;i<list.size();++i) {
            TreeNode * temp = list[i];		
            temp->left = cur;				//第二个节点的前驱指向第一个节点
            cur->right = temp;			//第一个节点的后继指向第二个节点
            cur = temp;
        }
        return head;
    }
};
```

