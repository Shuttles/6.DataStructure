# 森林

1. 由若干棵互不相交的树组成的，两棵树之间分别独立，没有交集。

2. 遍历
   + 先根遍历
   + 后根遍历





# 并查集

参考资料：

https://blog.csdn.net/dm_vincent/article/details/7655764

以及

https://blog.csdn.net/dm_vincent/article/details/7769159

## 用途

==维护连通性关系，==解决连通性问题，用于求不相交集合并集。

### 连通性问题



<img src="https://wx4.sinaimg.cn/mw690/005LasY6gy1gc6hvkybzbj312h0u0agh.jpg" alt="img" style="zoom: 200%;" />

1. 基于染色的思想，一开始所有点的颜色不同。
2. 连接两个点的操作，可以看成将一种颜色的点染成另一种颜色。
3. 如果两个点颜色一样，证明联通，否则不连通。
4. 这种方法叫做并查集的：Quick-Find算法。



### Quick-Find算法

#### 结构定义

```C
typedef struct UnionSet {
  int *color;//下标是每个点，对应的数组元素是每个点的颜色
  int n;//表示点的个数
} UnionSet;
```

#### 结构操作

```C
UnionSet *init_UnionSet(int n) {
  UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
  u->color = (int *)malloc(sizeof(int) * (n + 1));//为了让下标从1开始
  u->n = n;
  for (int i = 1; i <= n; i++) {
    u->color[i] = i;//每个点的初始元素是自己!!!
  }
}

void clear_UnionSet(UnionSet *u) {
  if (!u) return ;
  free(u->color);
  free(u);
  return ;
}
```



#### 联通操作：

***<u>将后者替换掉前者所联通的所有点的数组元素</u>***

```C
//下面是查找点的颜色操作
int find(UnionSet *u, int x) {
  return u->color[x];
}

//下面是联通操作
int merge(UnionSet *u, int a, int b) {
  if (find(u,a) == find(u, b)) return 0;
  int color_a = u->color[a];
  for (int i = 1; i <= u->n; i++) {
    if (u->color[i] - color_a) continue;
    u->color[i] = u->color[b];
  }
  return 1;
}
```



#### 总结

1. 联通判断：O(1)
2. 合并操作：O(n)



#### 思考

1. quick-find算法的联通判断非常快，可是合并操作非常慢。
2. 本质上问题中只是需要知道一个点与哪些点的颜色相同。
3. 而若干点的颜色可以通过间接指向同一个节点。
4. ***<u>合并操作时，实际上是将一棵树作为另一棵树的子树。</u>***(这一点非常重要！！！！！！！！！！)



### Quick-Union算法

#### 结构定义

```c
typedef struct UnionSet {
  int *father;//下标是点，数组元素是其联通组的代表元素
  int n;
} UnionSet;
```



#### 结构操作

```c
UnionSet *init_UnionSet(int n) {
	UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
  u->father = (int *)malloc(sizeof(int) * (n + 1));
  u->n = n;
  for (int i = 1; i <= n; i++) {
    u->father[i] = i;//一开始每个点的代表元素是自身
  }
  return u;
}

void clear_UnionSet(UnionSet *u) {
  if (!u) return ;
  free(u->father);
  free(u);
  return ;
}
```



#### 联通操作：

***<u>若前者的代表元素为本身，则将后者的代表元素替换掉前者的代表元素(认后者为大哥)。若不为本身，追溯到代表元素为本身的元素去替换。</u>***

#### 图解

![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gc6j47at20j318c0u01kx.jpg)

![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1gc6j4ltwqgj31kc0u0b29.jpg)

```C
//下面是寻找x点的所在联通组的代表元素的操作
//代表元素即为他们组所在的树的根节点的序号！！！！
int find(UnionSet *u, int x) {
  if (u->father[x] == x) return x;//递归程序的出口
  return find(u, u->father[x]);//妙啊！！！
}

//下面为联通操作！
int merge(UnionSet *u, int a, int b) {
  int fa = find(u, a), fb = find(u, b);
  if (fa == fb) return ;
  u->father[fa] = fb;//将前者的代表元素改成后者的代表元素！！！
  return 1;
}
```



#### 总结

1. 联通判断：树高 O(logn)~O(n)
2. 合并操作：树高 O(logn)~O(n) (有可能会退化成链表)

![img](https://wx4.sinaimg.cn/mw690/005LasY6gy1gc6j4t3n8uj31we0sy7wh.jpg)

看到这条链表，有没有想起前面讲过的一句话？？

***<u>合并操作时，实际上是将一棵树作为另一棵树的子树。</u>***(这一点非常重要！！！！！！！！！！)



#### 思考

1. 极端情况下会退化成一条链表。
2. 将节点数量多的接到少的树上面，导致了退化。
3. 将树高 深的接到浅的上面，导致了退化。

#### 优化

若要改进，是按照节点数量还是按照树的高度为合并参考？

还是得看ASL！！

![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gc6s7pup0ej31ur0u01kx.jpg)

![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gekaenom7xj31bn0u0npd.jpg)

Sa是A树的结点个数，La是A树的平均查找长度，右边分别是A树作为子树和B树作为子树的ASL，可以看出，结点个数少的，ASL小！所以按结点个数优化！！

### Weighted Quick-Union算法

#### 结构定义

```C
typedef struct UnionSet {
  int *father, *size;//size数组用来记录每个组的结点数量，以结点数量为权重！！！！
  int n;
} UnionSet;
```

#### 结构操作

```C
UnionSet *init_UnionSet(int n) {
  UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
  u->father = (int *)malloc(sizeof(int) * (n + 1));
  u->size = (int *)malloc(sizeof(int) * (n + 1));
  u->n = n;
  for (int i = 1; i <= n; i++) {
    u->father[i] = i;
    u->size[i] = 1;//开始时每组结点都只有一个
  }
}
```



#### 联通操作

***<u>在合并两棵树之前，先比较两棵树的结点个数，将结点个数少的变成结点个数多的树的子树！(这样能尽量保持整棵树的平衡)！！！</u>***

##### 图解

![img](https://wx4.sinaimg.cn/mw690/005LasY6gy1gc6qg3ttrnj31j80u0b29.jpg)

![img](https://wx4.sinaimg.cn/mw690/005LasY6gy1gc6qgalg2uj318j0u04qp.jpg)

![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1gc6qglo2ngj31k90u0b29.jpg)

![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gc6qgui7sbj31p90u0hdt.jpg)

代码如下

```C
int find(UnionSet *u, int x) {
  if (u->father[x] == x) return ;
  return find(u, u->father[x]);
}

int merge(UnionSet *u, int a, int b) {
  int fa = find(u, a), fb = find(u, b);
  if (fa == fb) return 0;
  //合并之前比较两棵树的结点多少
  if (u->size[fa] > u->size[fb]) {
    u->father[fb] = fa;
    u->size[fa] += u->size[fb];
  } else {
    u->father[fa] += fb;
    u->size[fb] += u->size[fa];
  }
  return 1;
}
```



#### 总结

![img](https://wx1.sinaimg.cn/mw690/005LasY6gy1gc6qwih96uj31w20u0b29.jpg)

推导：

![img](https://wx1.sinaimg.cn/mw690/005LasY6gy1gc6rn7ym4ej31tv0u01kx.jpg)





#### 优化

即做路径压缩，使每棵树的最终形态变为只有一个根节点、高度为2的树！

其实就只要find出来的最终代表元素赋给father就行了！！

```C
int find(UnionSet *u, int x) {
  return u->father[x] = (u->father[x] == x ? x : find(u, u->father[x]));
}

int merge(UnionSet *u, int a, int b) {
  int fa = find(u, a), fb = find(u, b);
  if (fa == fb) return 0;
  if (u->size[fa] < u->size[fb]) swap(fa, fb);
  u->father[fb] = fa;
  u->size[fa] += u->size[fb];
}
```

![img](https://wx2.sinaimg.cn/mw690/005LasY6gy1gc7ljidpwdj30kw0aotau.jpg)



### 总结

![img](https://wx4.sinaimg.cn/mw690/005LasY6gy1gc6rbxdzspj31ou0segs7.jpg)







# 加权并查集

## 1.例题

### 1.1猜拳(HZOJ-72)

分析

1. 其实输赢关系本质上也是一种联通关系，我知道我能赢你，就知道你能输给我；我知道另一个人和你的输赢关系，就能知道那个人和我之间的输赢关系！



权值设计

![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gen3u1lp30j31290u0e81.jpg)

![img](https://wx1.sinaimg.cn/mw690/005LasY6gy1gen3wvhtnij315v0u04qp.jpg)

连通权值推导

![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gen3zmfvq7j31e90u04qp.jpg)



路径压缩

1. 当回溯到该节点时，其父结点已经挂到root上了！！

![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gen43d6wg6j31es0pskbi.jpg)



