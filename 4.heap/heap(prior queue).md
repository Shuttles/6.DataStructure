# 本质

堆的本质其实就是一棵完全二叉树！！(由于其特性可用顺序表来存储)

由于堆是一棵完全二叉树，堆的插入和删除操作的时间复杂度为O(logN), logN指的就是这棵完全二叉树的高度。

![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gc1j7jvtpfj31l70u0k2a.jpg)

# 分类

## 大顶堆

1. 定义：每个根结点的data>左右子树的任何结点的data(堆序性）



![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1gc1k62m8arj30ti0ootcf.jpg)

## 小顶堆

1. 定义：每个根结点的data＞左右子树的任何结点的data(堆序性)

![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1gc1k69zjtoj30ve0ns781.jpg)



# 结构定义

```C
typedef struct Heap {
  int *data;
  int cnt, size;
} Heap;
```



# 结构操作

1. 初始化与回收空间

   ```C
   Heap *init_Heap(int n) {
     Heap *q = (Heap *)malloc(sizeof(Heap));
     q->data = (int *)malloc(sizeof(int) * (n + 1));
     q->cnt = 0;
     q->size = n;
     return q;
   }
   
   void clear_Heap(Heap *q) {
     if (!q) return ;
     free(q->data);
     free(q);
     return ;
   }
   ```

2. 一些基础操作

   ```C
   int empty(Heap *q) {
     return q->cnt == 0;
   }
   
   int top(Heap *q) {
     return q->data[1];
   }
   ```

   

3. push(在尾部插入并向上调整)(由此可以衍生出一种时间复杂度为O(nlogn)的建堆方法)

   ![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1gc1k6g77j0j31lz0u0k1n.jpg)

   ```C
   int push(Heap *q, int val) {
     if (!q) return 0;
     if (q->cnt == q->size) return 0;
     q->data[++q->cnt] = val;
     //下面是自本身到父结点的调整
     int ind = q->cnt;
     while (ind >> 1 && q->data[ind] > q->data[ind >> 1]) {
       swap(q->data[ind], q->data[ind >> 1]);
       ind >>= 1;
     }
     return 1;
   }
   ```

   

4. 弹出(在头部弹出并向下调整)

   ![img](https://wx4.sinaimg.cn/mw690/005LasY6gy1gc1k6na08dj31lu0u0ajh.jpg)

```C
int pop(Heap *q) {
  if (!q) return 0;
  if (empty(q)) return 0;
  q->data[1] = q->data[q->cnt--];//把最后一个元素赋值到头部，相当于弹出
  //下面是自本身到左右孩子的向下调整
  int ind = 1;
  while ((ind << 1) <= q->cnt) {
    int temp = ind, l = ind << 1, r = ind << 1 | 1;
    if (q->data[l] > q->data[temp]) temp = l;
    if (r <= cnt && q->data[r] > q->data[temp]) temp = r;
    if (temp == ind) break;
    swap(q->data[temp], q->data[ind]);
    ind = temp;
  }
  return 1;
}
```



# 线性建堆

1. 原来的自下而上(本结点与父结点比较)的建堆方法：结点调整的时间复杂度为O(nlogn)， 空间复杂度为O(n)。

   推导：

2. 线性建堆法：自上而下(父结点与左右孩子比较)， 时间复杂度为O(n), 不需要额外开空间，给一个数组，就可以在原数组上线性建堆。

   通俗理解：整体(整个完全二叉树)自下而上，按层遍历

   ```C
   void down_update(int *arr, int n, int ind) {
     while ((ind << 1) <= n) {//当左孩子结点存在， 自上而下比较三元组
       int temp = ind, l = ind << 1, r = ind << 1 | 1;//l是左孩子下标，r是右孩子下标
       if (arr[l] > arr[temp]) temp = l;
       if (r <= n && arr[r] > arr[temp]) temp = r;
       if (temp == ind) break;//如果父结点比左右孩子都大，那么就不必再调整
       swap(arr[temp], arr[ind]);
       ind = temp;
     }
     return ;
   }
   
   void build(int *arr, int n) {//n是这个数组的长度
     --arr;
     for (int i = n >> 1; i >= 1; i--) {//从最后一个结点起，按层次遍历，自底向上线性建堆
       down_update(arr, n, i);
     }
   }
   ```

   



# 具体应用场景

## 堆排序

1. 以大顶堆为例

![img](https://wx4.sinaimg.cn/mw690/005LasY6gy1gc0ypl68moj31l80u0an4.jpg)

2. 口诀：
   1. 将堆顶元素(最大值)与堆尾元素交换
   2. 将此操作看做是堆顶元素弹出操作
   3. 调整堆(自上而下)
3. 堆排序是一种高效重要的排序方法，时间复杂度可以达到O(nlogn)。
4. 从原理上看，堆排序和选择排序有些类似，每次选一个最大值和当前元素交换，不过这里是利用堆来维护，调整效率比选择排序高了很多，调整的时间复杂度可以达到O(logn)， 要交换n次，调整n次，所以总的时间复杂度为O(nlogn)。

所以，如果是大顶堆进行堆排序，那么排好序的应该是从小到大的序列！！！

代码如下

时间复杂度为O(nlogn)

```C
void heap_sort(int *arr, int n) {
  --arr;
  //下面是线性建堆
  for (int i = n; i >= 1; i--) {
    down_update(arr, n, i);
  }
  //下面是真正的排序
  for (int i = n; i > 1; i--) {
    swap(arr[1], arr[i]);//将堆顶元素与堆尾元素交换
    down_update(arr, i - 1, 1);
  }
  return ;
}
```



## 任务调度





# 经典例题

## 蒜头君捡石子

1. 及其考验抽象能力！！！(我抽象不出来，借鉴的光哥的)

2. 题面：

   蒜头君下班会走过一条笔直的路，一天，他发现道路上有很多石子，调皮的他决定玩个游戏。

   游戏规则如下：当蒜头君遇到第i颗石子时，如果i是奇数，他会把这个石子往前扔di个单位距离， 如果i是偶数，他就会忽略这块石子。如果同一时刻遇到多颗石子，优先处理di小的石子(如果此时有两颗石子，di小的被当做遇到的第n个石子，di大的被当做第n+1个石子)。蒜头君的初始位置为0，当他走到最后一颗石子，且这颗石子不再被往前扔的时候则停止，他想知道自己能走的最长距离是多少。

   <img src="https://wx3.sinaimg.cn/mw690/005LasY6gy1gc21h1mw7cj30le15otci.jpg" alt="img" style="zoom:50%;" />

3. 我的思路：

   + 一开始我想应该要存下这个石子，是用数组呢还是什么呢，后来看到优先处理di小的石子，我考虑用一个优先队列存储这些石子，就按di来排优先级，可是如何处理它们的位置关系呢？难道要再开一个优先队列按位置来排优先级？那样未免太麻烦了吧。。。
   + 我在如何抽象往前走和遇到石子的问题上也纠结了很久，一开始想的是先定义一个ind = 0，然后每次++(走一步)， 直到遇到石子，可是如何遇到石子呢？难不成查找一个优先队列里有没有 位置== ind的？
   + 最后我也不知道如何抽象停止。。。。(我太菜了。。)

4. 光哥的思路：

   + 直接用一个优先队列来存石子就好了！怎么定优先级呢？自己写一个cmp！把位置和di都包含进去！！

   + 如何抽象一直往前走和停止？

     while (!empty(q))，然后每次获取堆顶元素(最近的也是di最小的)(这就是模拟遇到石子！！！)， 接着每次都要弹出堆顶元素，将该堆顶元素的di赋给最终蒜头君走的距离(这样就可模拟蒜头君的走路了！！只不过是跳着走的！！！)， 然后在外面定义一个变量sum记录这是遇到的第几个石头并且每次++，最后，如果是sum奇数就往前扔di，并且再次入队列！！！如果sum是偶数就不管它，不入队列！！！(这样只要队列不空，蒜头君就一直在走，这样就模拟了停止！！)

5. 代码如下：

   ```C
   #include <stdio.h>
   #include <stdlib.h>
   #define swap(a, b) {\
       __typeof(a) __temp = (a);\
       (a) = (b), (b) = __temp;\
   }
   
   
   typedef struct Stone {
       int p, d;
   } Stone;
   
   typedef struct Heap {
       Stone *data;
       int cnt, size;
   } Heap;
   
   Heap *init_Heap(int n) {
       Heap *q = (Heap *)malloc(sizeof(Heap));
       q->data = (Stone *)malloc(sizeof(Stone) * (n + 1));
       q->cnt = 0;
       q->size = n;
       return q;
   }
   
   void clear_Heap(Heap *q) {
       if (!q) return ;
       free(q->data);
       free(q);
       return;
   }
   
   int empty(Heap *q) {
       return q->cnt == 0;
   }
   
   Stone top(Heap *q) {
       return q->data[1];
   }
   
   //这个函数极为关键！！！
   int cmp_Stone(Stone a, Stone b) {
       if (a.p < b.p) return 1;
       if (a.p == b.p && a.d < b.d) return 1;
       return 0;
   }
   
   void down_update(Heap *q, int n, int ind) {
       if (!q) return ;
       while ((ind << 1) <= n) {
           int temp = ind, l = ind << 1, r = ind << 1 | 1;
           if (cmp_Stone(q->data[l], q->data[temp])) temp = l;
           if (r <= n && cmp_Stone(q->data[r], q->data[temp])) temp = r;
           if (temp == ind) break;
           swap(q->data[temp], q->data[ind]);
           ind = temp;
       }
       return ;
   }
   
   int pop(Heap *q) {
       if (!q) return 0;
       if (empty(q)) return 0;
       q->data[1] = q->data[q->cnt--];
       down_update(q, q->cnt, 1);
       return 1;
   }
   
   int push(Heap *q, Stone s) {
       if (!q) return 0;
       if (q->cnt == q->size) return 0;
       q->data[++q->cnt] = s;
       int ind = q->cnt;
       while ((ind >> 1) && cmp_Stone(q->data[ind], q->data[ind >> 1])) {
           swap(q->data[ind], q->data[ind >> 1]);
           ind >>= 1;
       }
       return 1;
   }
   
   
   int main() {
       int N;
       scanf("%d", &N);
       while (N--) {
           int n;
           scanf("%d", &n);
           Heap *q = init_Heap(n);
           for (int i = 0; i < n; i++) {
               Stone s;
               scanf("%d%d", &s.p, &s.d);
               push(q, s);
           }
           int distance = 0, sum = 1;
           while (!empty(q)) {
               Stone s = top(q);
               pop(q);
               distance = s.p;
               if (sum % 2) {
                   s.p += s.d;
                   push(q, s);
               }
               ++sum;
               //sum记录遇到的第几个石子
           }
           printf("%d\n", distance);
           clear_Heap(q);
       }
       return 0;
   }
   ```

   

6. 反思：还是得多做题，多提升抽象问题的能力！！

