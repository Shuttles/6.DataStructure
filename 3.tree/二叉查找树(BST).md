# 1.二叉查找树(BST)

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









# 2.平衡二叉排序树



1. 引出

   ==如果插入BStree的顺序不当，就有可能使BStree退化成一个链表，因此查找效率就从O(logn)退化到了O(n)==

2. 所以就来了平衡二叉排序树

   ==每种平衡二叉排序树的“平衡”定义是不一样的！==



## 2.1AVL树

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











## 2.2红黑树

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

