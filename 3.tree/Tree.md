

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

   + 在递归程序设计时你只需要这么想：所到的每个结点都是root结点，都有其左子树、右子树！！！
   + 返回值基本都是Node *类型的！！(比较我实现的错误的insert和泽哥实现的正确的insert就可以懂了)

   

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

   刘晨旭错误的改版，也是没注意到形参和实参的区别！
   
   ```C
   Node *insertNode(Node *root, int val, int *flag) {
     if (!root) {
       *flag = 1;
       return root = init_Node(val);//只是给指针变量(形参)赋值，并不改变实参的值！！！
     }
     if (val == root->data) return root;
     if (val < root->data) insertNode(root->lchild, val, flag);
     else insertNode(root->rchild, val, flag);
     return root;
   }
   ```

对比反转二叉树！！！

```c
struct TreeNode* invertTree(struct TreeNode* root){
    if (!root) return NULL;
    struct TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;
    root->left = invertTree(root->left);
    root->right = invertTree(root->right);
    return root;
}

//倒数2、3行可以改写成
invertTree(root->left);
invertTree(root->right);
//可以这么改写是因为最后返回值设计的是Node类型！！！
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

2. 中序遍历：左 根 右

3. 后序遍历：左 右 根

4. 层序遍历：利用Queue

```C
void level_order(Tree *tree) {
  	if(!tree) return ;
  	if (!tree->root) return ;
    Queue *q = init_Queue(MAX_N + 5);
    push(q, tree->root);//先将根节点入队
    while (!empty(q)) {
        if (front(q)->lchild) {
            push(q, front(q)->lchild);
        }
        if (front(q)->rchild) {
            push(q, front(q)->rchild);
        }
        (front(q) != tree->root) && printf(" ");
        printf("%c ", front(q)->data);
        pop(q);
    }
    return ;
}
```

5. 至少知道2种遍历方式就能反推出这棵树(有一种必须为中序遍历！)！

   + 已知二叉树的先序遍历和中序遍历，求后序遍历。

     算法过程如下：

     我们可以在先序遍历里知道根节点的编号，在中序遍历中就可以找到根节点所在位置(strchr函数)， 那么位置前面的结点就是根结点的左子树上的结点，位置后面的结点就是右子树上的结点。

     按照以上函数***<u>递归</u>***建立起一个二叉树！！！！！

     代码如下

     ```C
     Node *build(char pre_str[], char in_str[], int len) {
       //给予的语义信息就是前一个字符串是该子树(理解成子树更好理解！！)的先序遍历，第二个字符串是中序遍历，len是这俩遍历的长度(即子树的结点个数)
       Node *root = init_Node(pre_str[0] & 15);//利用先序遍历找到根结点的值并生成根结点
       int ind = strchr(in_str, pre_str[0]) - in_str;//找到中序遍历中根结点所在的位置,这也是左子树的元素个数！！！
       if (ind > 0) {//如果左子树存在
         root->lchild = build(pre_str + 1, in_str, ind);//递归建立左子树
       }
       if (len - ind - 1 > 0) {//如果右子树存在
       	root->rchild = build(pre_str + ind + 1, in_str + ind + 1, len - ind - 1);//递归建立右子树
       }
       return root;
     }
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

6. 广义表转二叉树
   + 利用栈来解决！因为栈可以解决具有完全包含关系的问题！
   + "("表示事件的开始，")"表示事件的结束！！！
   + 遇到普通字符不入栈，只是简单init_Node，只有遇到"("才表示事件开始，表示后面是temp的子树，所以将temp入栈并且同时flag清零！！！！遇到")"表示事件结束，即栈顶元素的子树结束了，所以将栈顶元素出栈！！！

```C
Node *transform(char *str, int *node_num) {
    Node *temp = NULL, *root = NULL;//root记录最后的根节点
    Stack *s = init_Stack(strlen(str));
    int flag = 0;//记录有无逗号
    int i = 0;
    while (str[i]) {
        switch (str[i]) {
            case '(': {//只有遇到左括号，前一个值才入栈！！！因为左括号表示这是一个新事件的开始！！即后面是前一个值的子树！！！
                push(s, temp);
                flag = 0;
                temp = NULL;
            } break;
            case ')': {
                root = top(s);
                pop(s);
            } break;
            case ',': {
                flag = 1;
                temp = NULL;
            } break;
            case ' ': break;
            default: {
                temp = init_Node(str[i]);
              	//为什么要判空呢？因为有可能这时是根节点！！
                if (!empty(s) && !flag) {
                    top(s)->lchild = temp;
                } else if (!empty(s) && flag) {
                    top(s)->rchild = temp;
                }
                (*node_num)++;
            } break;
        }
        ++i;
    }
    clear_Stack(s);
    if (temp && !root) root = temp;//防止只有一个根节点，如A
    return root;
}
```



## 二叉树的线索化

1. 目的：为了解决系统栈爆栈问题
2. 可行性：
   1. n个结点的树有n+1个空指针域。(2n - (n-1))。
3. 







## 二叉查找树(BST)

#### 综述

又称二叉排序树，二叉搜索树(Binary Search Tree)

1. 性质：

   + 左子树<根结点
   + 右子树＞根结点
   + 一般而言，BST上结点的值都是唯一的。
   + 如果中序遍历BST，会得到一个从小到大的序列。
   + BST的插入和查找效率相对较高，最坏情况下时间复杂度为O(n),期望的时间复杂度为O(logn)。

2. 用途：

   ==解决与排名相关的检索需求==
   
   > 如何解决呢？比如说求排名第K名的成绩
   >
   > 这要分三种情况！
   >
   > 1. 根节点左子树的结点个数>=k 则第k名在左子树
   > 2. 根节点左子树的结点个数 == k - 1，则第k名为根节点
   > 3. 根节点左子树的结点个数 < k - 1，则第k名在右子树的第`k - size(右) - 1`名
   >
   > ***<u>所以，就得在每个结点的结构定义中增加一个字段，就是以这个结点为root结点的树的结点个数size！</u>***
   
   



#### 结构定义

```C
typedef struct Node {
  int key;
  struct Node *lchild, *rchild;
} Node;
```



#### 结构操作

##### 初始化与回收

```C
Node *init_Node(int key) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->key = key;
  node->lchild = node->rchild = NULL;
  return node;
}

void clear_Node(Node *root) {
  if (!root) return ;
  clear_Node(root->lchild);
  clear_Node(root->rchild);
  free(root);
  return ;
}
```

##### 插入

1. 有一个设计技巧，就是返回值的设计！
2. 返回值设置为==插入之后的那个子树的根节点地址==！！

```C
//仔细揣摩返回值设计的巧妙!!!
Node *insert(Node *root, int key) {/*向以root为根节点的子树中插入key*/
  if (!root) {
    return init_Node(key);
  }
  if (root->key == key) return root;/*插入的值已经存在*/
  if (root->key > key) root->lchild = insert(root->lchild, key);
  else root->rchild = insert(root->rchild, key);
  return root;
}
```

##### 删除

###### 图解

![img](https://wx4.sinaimg.cn/mw690/005LasY6gy1gc7uvjwktij31cb0u0x0t.jpg)

+ 删除度为0的结点

  直接删除就好了

+ 删除度为1的结点

  ![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gc7uvxhzpbj31ck0u0nja.jpg)

  ![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gc7uw4ct0qj31at0u0tu9.jpg)

+ 删除度为2的结点

  ![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1gc7uwa6zbwj31k10u0b0h.jpg)

  因为其前驱或者后继一定是==度为1或0的结点==！！！

  ![img](https://wx1.sinaimg.cn/mw690/005LasY6gy1gc7uwgydazj31hq0u0no1.jpg)

  ![img](https://wx1.sinaimg.cn/mw690/005LasY6gy1gc7uwna9grj31jo0u0x4s.jpg)

  ![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gc7uwzx03jj31k50u0qsa.jpg)

  1. 删除操作的返回值设计得也很巧妙！！
  2. 返回值设置为==删除完这个结点之后的子树的根结点地址==
  
  

```C
//下面是寻找当前结点的前驱结点的方法
//当前结点的前驱就是小于当前结点的最大结点，就是先往左走一步，再一直往右走！！！！
Node *predecessor(Node *root) {
  Node *temp = root->lchild;
  while (temp->rchild) temp = temp->rchild;
  return temp;
}

//返回值设计得妙啊！！！！
Node *erase(Node *root, int key) {/*在以root为根节点的子树中删除一个值为key的结点*/
  if (!root) return ;//表示没找到这个值
  if (key < root->key) root->lchild = erase(root->lchild, key);
  else if (key > root->key) root->rchild = erase(root->rchild, key);
  else {
    //接下来是正式删除
    if (root->lchild == NULL || root->rchild == NULL) {
      //度为0或度为1的结点
      Node *temp = root->rchild ? root->rchild : root->lchild;
      free(root);
      return temp;/*如果为叶子结点就会返回NULL*/
    } else {
      //度为2的结点！！
      //要找到前驱或者后继，此处以前驱为例
      Node *temp = predecessor(root);
      root->key = temp->key;
      root->lchild = erase(root->lchild, temp->key);
    }
  }
  return root;
}
```









### 平衡二叉排序树



1. 引出

   ==如果插入BStree的顺序不当，就有可能使BStree退化成一个链表，因此查找效率就从O(logn)退化到了O(n)==

2. 所以就来了平衡二叉排序树

   ==每种平衡二叉排序树的“平衡”定义是不一样的！==



#### AVL树

##### 1. 基本概念

![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1ge3p8h0k3jj31k10u07wh.jpg)

1. ==可以看出它的“平衡定义”==

2. 思考

   ![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1ge3pgfzic5j31d70u0ncn.jpg)

   + 显然只有第二个问题中的下限比较难求，我们设`low(H)`为高度H的AVL树的结点数量的下限

   + 则![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1ge5tsqt0e6j31280eu12n.jpg)

   + `low(H) = low(H - 1) + low(H- 2) + 1`

   + 所以答案为

     ![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1ge5tuezd4lj31ra0fg4ax.jpg)

   + 下限的公式和斐波那契数列的公式很相似，所以==增长速率也应相似==

     fib数列的增长速度约为1.618， 取个近似为1.5

     则![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1ge5tyaab00j311w0u0e81.jpg)

   + ==所以，AVL树的结点上下界都是logN级别的！==



##### 2. 调整策略

1. ***<u>最基本的调整策略：</u>***左/右旋

   ==其实就是抓着第一个失衡的结点进行左/右旋！==

   也称 ***<u>转一下，砍一刀！</u>***

   ![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1ge5u4p4cn8j31t80u04qp.jpg)

   + 就是抓着K1结点左旋！
   + 注意这种情况会发生在==删除K2的子节点之后==！(==把这种情况当做RR==)

   ![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1ge5u4sdytrj31uh0u04qp.jpg)

   + 右旋与左旋相对称！

2. ***<u>失衡调整</u>***

   以下的失衡类型是站在==插入结点的角度==考虑的！但是删除结点的情况也适用！

   并且都是从下往上找第一个失衡的结点，站在那个结点来看的！

   ![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1ge5u9gjpsrj31l50u07wh.jpg)

   + LL

     + 就是第一个失衡的结点(K1)的左子树的左子树更重一些！

     + 高度关系及调整策略

       ![img](https://wx1.sinaimg.cn/mw690/005LasY6gy1ge5uopwq4cj31ca0u0kjl.jpg)

     + LR

       + 高度关系

         ![img](https://wx1.sinaimg.cn/mw690/005LasY6gy1ge5ure3amlj319n0u0npd.jpg)

       + 调整策略

         先抓着==K2==(此时不是抓着第一个失衡的结点)进行==小==左旋变成LL型，然后右旋(抓着第一个失衡的结点==K1==)即可

         ![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1ge5uwdvqu6j31q10u0b29.jpg)

         

         



##### 3.代码演示

```c++
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key, h;/*定义在这更节省存储空间*/
    struct Node *lchild, *rchild;
} Node;

/*骚操作, 用NIL代替NULL*/
Node _NIL;
Node *NIL = &_NIL;
__attribute__((constructor))
void init_NIL() {
    NIL->key = 0;
    NIL-h = 0;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}


Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NIL;
    p->h = 1;
    return p;
}

void clear(Node *root) {
    if (root = NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void UpdateHeight(Node *root) {
    /*用了NIL之后就不用担心左右子树为NULL了！！！！*/
    int h1 = root->lchild->h;
    int h2 = root->rchild->h;
    root->h = (h1 > h2 ? h1 : h2) + 1;
    return ;
}

Node *left_rotate(Node *root) {
    /*定义一个temp作为旋转完的根节点*/
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    
    /*更新树高*/
    /*只有新老根节点h可能发生变化*/
    UpdateHeight(root);
    UpdateHeight(temp);
    return temp;
}

Node *right_rotate(Node *root) {
    /*定义一个temp作为旋转完的根节点*/
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    
    /*更新树高*/
    /*只有新老根节点h可能发生变化*/
    UpdateHeight(root);
    UpdateHeight(temp);
    return temp;
}

Node *maintain(Node *root) {/*返回值就是调整完之后这棵子树的root结点*/
    if (abs(root->lchild->h - root->rchild->h) <= 1) return root;/*不用调整*/
    /*进行调整*/
    if (root->lchild->h > root->rchild->h) {
        /*第一个字母是L*/
        if (root->lchild->rchild->h > root->lchild->lchild->h) {
            /*第二个字母是R*/
            /*抓住根节点的左孩子进行左旋*/
            root->lchild = left_rotate(root->lchild);
        }   
        root = right_rotate(root);/*抓住根节点(第一个失衡的结点)进行右旋*/
    } else {
        if (root->rchild->lchild->h > root->rchild->rchild->h) {
            root->rchild = right_rotate(root->rchild);
        }   
        root = left_rotate(root);
    }
    return root;
}

Node *insert(Node *root, int key) {
    if (root = NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    
    /*树高调整*/
    UpdateHeight(root);
    
    return maintain(root);/*这个方法是AVL树的核心！*/
}

Node *predeccessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key > key) root->lchild = erase(root->lchild, key);
    else if (root->key < key) root->rchild = erase(root->rchild, key);
    else {
        if (root->lchild == NIL || root->rchild == NIL) {
            /*度为0或1*/
            Node *temp = (root->lchild == NIL ? root->rchild : root->lchild);
            free(root);
            return temp;
        } else {
            Node *temp = predeccessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    /*更新树高*/
   	UpdateHeight(root);
    return maintain(root);
}

void output(Node *root) {
    if (root == NIL) return;
    output(root->lchild);
    printf("%d [%d, %d]\n", root->key, root->lchild->key, root->rchild->key);
    output(root->rchild);
    return ;
}


int main() {
    int val, op;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
        }
        output(root);
    }
    return 0;
}
```

PS：在本目录中有改进版！(增加了几个宏)











#### 红黑树

##### 1. 五个条件

1. 每个节点非黑即红
2. 根节点是黑色的
3. 叶结点(NIL)是黑色的
4. 如果一个节点是红色，则它的两个子节点都是黑色的
5. 从根节点出发到所有叶节点路径上，黑色节点数量相同
   + 如果确定了黑色节点数量为n，那么最短路径为n，最长路径为2n
   + ==这个条件从路径长度上面来限制红黑树两棵子树之间的高度差==， 最大高度差就是一倍
   + 也就是从树高方面去限定了平衡条件
   + 因此，可以将红黑树看成规则更加松散的AVL树
   + 比如给你一棵AVL树，一定可以涂成红黑树
   + 因此，红黑树本质上也是通过树高来控制平衡条件的
   + ==红黑树不仅可以通过旋转来调整平衡，也可以通过改变节点颜色来调整平衡==



##### 2.调整策略

1. 插入调整站在***<u>祖父节点</u>***看
2. 删除调整站在***<u>父节点</u>***看
3. 插入和删除的情况处理一共五种



##### 3.插入调整的情况--为了解决两红相邻问题

1. uncle为红色的情况

   改成红上顶

2. uncle为黑色的情况





##### 4.删除调整的情况--为了解决双重黑节点

兄弟结点为黑色

1. 情况一--兄弟结点子节点都为黑色

   brother调整为红，x减少一重黑色，father增加一重黑色



下面是兄弟结点子节点有红色的情况

1. 情况二-RL

   进行小右旋，再改变俩颜色，就可变成RR类型

   

2. 情况三--RR(双重黑节点的右brother为黑且其rchild为红)

   进行大左旋，接着将其上顶三角形改成“原根节点颜色-黑-黑”

   



兄弟结点为红色的情况--通过左/右旋一定可以转化为兄弟结点为黑色的情况

