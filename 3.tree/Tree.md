

# 综述

1. 树形结构广泛存在我们的现实生活里，下面两张图就是树形结构的例子。

   <img src="https://wx1.sinaimg.cn/mw690/005LasY6gy1gby6eremkuj30nu0eygpm.jpg" alt="img" style="zoom:50%;" />

   第一张是Linux文件系统结构，第二张是美国福特汽车公司的汽车家谱图。类似的树形结构还有很多，它们都可以抽象成数据结构里的树。数据结构中的树和自然界里的树相同的是，他们都有且仅有一个树根，树上的元素都是从树根衍生出来的。不同的则是自然界里的树，树根在下面。而数据结构里的树，树根在上面。

2. 一些概念：

   子树、根、度、高度与深度(分为树的高度与深度和某个结点的高度与深度)

3. 抽象概念：

   1. 结点--集合
      + 根节点相当于全集
      + 子树相当于子集

   2. 边--对应关系

4. 链表是特殊的一棵树，只有一棵子树

5. 性质：

   1. 结点个数 = 边数+ 1

   # 二叉树

   ## 重要性：

   N叉树(n任意)可以转化为二叉树！也就是说，可以将非确定性问题转化为确定性问题！！

   ## 性质

   ### 逻辑上

1. 第i层最多有pow(2, i - 1)个结点。
2. 深度为k的二叉树最多有pow(2, k) - 1个结点。(等比数列求和)
3. 任意一棵二叉树，n0 = n2 + 1， 其中n0是度为0的结点，n2是度为2的结点。



### 实现上

1. 二叉树的结构操作与递归密切相关！！！

   在递归程序设计时你只需要这么想：所到的每个结点都是root结点，都有其左子树、右子树！！！



#### 结构定义

```C
typedef struct Node {
  int data;
  struct Node *lchild, *rchild;
} Node ;

typedef struct Tree {
  Node *root;
  int n;
} Tree
```



#### 结构操作

1. 初始化与回收空间

```C
Node *init_Node (int val) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = val;
  node->rchild = node->lchild = NULL;
  return node;
}

Tree *init_Tree() {
  Tree *tree = (Tree *)malloc(sizeof(Tree));
  tree->root = NULL;
  tree->n = 0;
  return tree;
}

void clear_Node(Node *root) {
  if (!root) return ;
  clear_Node(root->lchild);
  clear_Node(root->rchild);
  free(root);//递归思想就体现在这！！！！！！！！！！
  return ;
}

void clear_Tree(Tree *tree) {
  if (!tree) return ;
  clear_Node(tree->root);
  free(tree);
  return ;
}
```

2. 以广义表形式输出

   ```C
   void outputNode(Node *root) {
     if (!root) return ;
     printf("%d ", root->data);
     if (!root->lchild && !root->rchild) return ;
     printf("(");
     outputNode(root->lchild);
     //if (!root->rchild) return ;如果这么写，可能会丢失")"
     if (root->rchild) printf(", ");//如果有右子树，就输个","
     outputNode(root->rchild);
     printf(")");
     return ;
   }
     
   void output(Tree *tree) {
     if (!tree) return ;
     printf("Tree(%d) = ", tree->n);
     outputNode(tree->root);
     printf("\n");
     return ;
   }
   ```

3. 以二叉排序树的形式插入

   ```C
   Node *insertNode(Node *root, int val, int *flag) {
     if (!root) {
       *flag = 1;
       return init_Node(val);
     }
     if (root->data == val) return root;
     if (val < root->data) root->lchild = insertNode(root->lchild, val, flag);
     else root->rchild = insertNode(root->rchild, val, flag);
     return root;
   }
   
   
   void insert(Tree *tree, int val) {
     if (!tree) return ;
     int flag = 0;//用来判断插入是否成功
     tree->root = insertNode(tree->root, val, &flag);
     tree->n += flag;
     return ;
   }
   ```

   错误的改版！！(我的错误尝试，但是更加深了我对形参实参的理解！！)

   + 我想还是像以前一样，用返回值来标记是否插入成功
   + 但是忽略了一个很重要的点！！
   + 就是 下面第三行其实是给传进来的指针变量(形参)赋值，函数结束后并不改变指针变量实参的值！！！

   ```C
   int insertNode(Node *root, int val) {
     if (!root) {
       root = init_Node(val);//只是给指针变量(形参)赋值，并不改变实参的值！！！
       return 1;
     }
     if (val == root->data) return 0;
     if (val < root->data) insertNode(root->lchild, val);
     else insertNode(root->rchild, val);
     return 1;
   }
   
   
   void insert(Tree *tree, int val) {
     if (!tree) return ;
     tree->n += insertNode(tree->root, val);
     return ;
   }
   ```

   









## 遍历

1. 前序遍历：根 左 右

```C
void pre_orderNode(Node *root) {
  if (!root) return ;
  printf("%d ", root->data);
  pre_orderNode(root->lchild);
  pre_orderNode(root->rchild);
  return ;
}

void pre_order(Tree *tree) {
  if (!tree) return ;
  printf("pre_order : ");
  pre_orderNode(tree->root);
  printf("\n");
}
```



1. 中序遍历：左 根 右
2. 后序遍历：左 右 根
3. 层序遍历：利用Queue
4. 至少知道2种遍历方式就能反推出这棵树(有一种必须为中序遍历！)！

```C

```



## N叉树转化成二叉树

1. 左孩子右兄弟表示法(也称十字链表法)



## 分类

### 中国版

1. 完全二叉树
2. 满二叉树(在国际版中叫完美二叉树)



### 国际版

1. 完全二叉树(同中国版)
2. 满二叉树(fully)



## 完全二叉树(complete binary tree)

1. 性质：
   1. 编号为i的子节点：
      + 左孩子编号：2 * i
      + 右孩子编号：2 * i + 1
   2. 由性质1可得，完全二叉树可以用连续空间存储(数组)





## 广义表表示形式

1. 空树 ：()
2. 一个根节点A：A()
3. 根节点A，左孩子B：A(B, )
4. 根节点A，左孩子B，右孩子C：A(B, C)
5. 二叉树转广义表，广义表转二叉树都必须会！

广义表转二叉树

代码如下

```C

```



## 二叉树的线索化

1. 目的：为了解决系统栈爆栈问题
2. 可行性：
   1. n个结点的树有n+1个空指针域。(2n - (n-1))。
3. 