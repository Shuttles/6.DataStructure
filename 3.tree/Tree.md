

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

   解决与排名相关的检索需求



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

```C
Node *insert(Node *root, int key) {
  if (!root) {
    return init_Node(key);
  }
  if (root->key == key) return root;
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

  因为其前驱或者后继一定是度为1的结点！！！

  ![img](https://wx1.sinaimg.cn/mw690/005LasY6gy1gc7uwgydazj31hq0u0no1.jpg)

  ![img](https://wx1.sinaimg.cn/mw690/005LasY6gy1gc7uwna9grj31jo0u0x4s.jpg)

  ![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gc7uwzx03jj31k50u0qsa.jpg)

  

```C
//下面是寻找当前结点的前驱结点的方法
//当前结点的前驱就是小于当前结点的最大结点，就是先往左走一步，再一直往右走！！！！
Node *predecessor(Node *root) {
  Node *temp = root->lchild;
  while (temp->rchild) temp = temp->rchild;
  return temp;
}

//返回值设计得妙啊！！！！
Node *erase(Node *root, int key) {
  if (!root) return ;//表示没找到这个值
  if (key < root->key) root->lchild = erase(root->lchild, key);
  else if (key > root->key) root->rchild = erase(root->rchild, key);
  else {
    //接下来是正式删除
    if (root->lchild == NULL || root->rchild == NULL) {
      //度为0或度为1的结点
      Node *temp = root->rchild ? root->rchild : root->lchild;
      free(root);
      return temp;
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

