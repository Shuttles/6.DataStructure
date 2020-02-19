# 本质

堆的本质其实就是一棵完全二叉树！！(由于其特性可用顺序表来存储)

![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gc1j7jvtpfj31l70u0k2a.jpg)

# 分类

## 大顶堆

1. 定义：每个根结点的data>左右子树的任何结点的data



![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1gc1k62m8arj30ti0ootcf.jpg)

## 小顶堆

1. 定义：每个根结点的data＞左右子树的任何结点的data

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

   

# 堆排序

以大顶堆为例

![img](https://wx4.sinaimg.cn/mw690/005LasY6gy1gc0ypl68moj31l80u0an4.jpg)

口诀：

1. 将堆顶元素与堆尾元素交换
2. 将此操作看做是堆顶元素弹出操作
3. 调整堆(自上而下)

所以，如果是大顶堆进行堆排序，那么排好序的应该是从小到大的序列！！！

代码如下

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

