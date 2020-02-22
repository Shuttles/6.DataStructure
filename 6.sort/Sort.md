# 分类

1. 稳定排序、非稳定排序

   + 稳定：

     插入排序

     1. 图解：

     ![img](https://wx4.sinaimg.cn/mw690/005LasY6gy1gc4h9rcyp8j31lj0u04qp.jpg)

     2. 口诀：

     + 将数组分成“已排序区”和“待排序区”。(已排序区在前面)
     + 将待排序区里的元素一个个插入到“已排序区里”。
     + 直到待排序区里没有元素为止。

     3. 时间复杂度：

        O(n^2)

     4. 代码如下

     ```c
     void insert_sort(int *arr, int n) {
       for (int i = 1; i < n; i++) {//一共n-1趟
         for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
           swap(arr[j], arr[j - 1]);
         }
       }
       return ;
     }
     ```

     

     

     

     冒泡排序

     0. 图解：

        ![img](https://wx4.sinaimg.cn/mw690/005LasY6gy1gc4hkce9qij31hw0u04qp.jpg)

     1. 口诀：

        + 将数组分成“已排序区”和“待排序区”。(已排序区在最后面)
        + 从头到尾遍历“待排序区”，若前面元素比后面大，则交换。
        + 每一轮都会将“待排序区”中最大的元素放到”已排序区“的开头！！！
        + 直到待排序区没有元素为止。

     2. 时间复杂度

        O(n^2)

     3. 优化：

     当发现某一次遍历中没有发现元素交换，那么就可以结束排序了。

     4. 代码如下：

        ```C
        void bubble_sort(int *arr, int n) {
          int times = 1;
          for (int i = 1; i < n && times; i++) {
            times = 0;
            for (int j = 0; j < n - i; j++) {
              if (arr[j] <= arr[j + 1]) continue;
              swap(arr[j], arr[j + 1]);
              times++;
            }
          }
          return ;
        }
        ```

        

     

     

     归并排序(可用于外部排序)

     <img src="https://wx1.sinaimg.cn/mw690/005LasY6gy1gc2x8uf0njj31hn0u04qp.jpg" alt="img"  />

     时间复杂度稳定在O(nlogn)

     1. 优势：

        可以用来外部排序，当要排序的数据量很大(超过内存时)， 可以先分治到可解规模(小于内存)，放入内存中排序，最后归并！

     2. 时间复杂度

        O(nlogn)

     3. 代码如下

        ```C
        void merge_sort(int *arr, int l, int r) {
          if (l == r) return ;
          int mid = (l + r) >> 1;
          merge_sort(arr, l, mid);
          merge_sort(arr, mid + 1, r);
          int x = l, y = mid + 1, loc = 0;
          int temp[n];
          while (x <= mid || y <= r) {
            if (x <= mid && (y > r || arr[x] <= arr[y])) {
              temp[loc++] = arr[x++];
            } else {
              temp[loc++] = arr[y++];
            }
          }
          for (int i = 0; i < n; i++) {
            arr[i] = temp[i - l];
          }
          return ;
        }
        ```

        

   

   

   + 非稳定：

     有选择排序、快排、堆排序、希尔排序等等

     选择排序

     ![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1gc31clhckgj31og0u04qp.jpg)

     1. 口诀：

        + 将数组分成”已排序区“和“非排序区”(已排序区在前面)。
        + 每一轮从”待排序区“中选择一个最小的元素放到”已排序区“的尾部。
        + 直到”待排序区“没有元素为止！

     2. 非稳定原因

        栗子：5 3 5 2 1

     3. 时间复杂度

        O(n^2)

     4. 代码如下

        ```C
        void select_sort(int *arr, int n) {
          for (int i = 0; i < n - 1; i++) {//一共n-1趟
            int ind = i;
            for (int j = i + 1; j < n; j++) {
              if (arr[ind] > arr[j]) ind = j;
            }
            if (ind - i) swap(arr[i], arr[ind]);
          }
          return ;
        }
        ```

        

     

     

     快速排序

     1. 口诀：

        

2. 内部排序、外部排序(指的是内存的内和外)

   根据排序过程中元素是否完全保存在内存中，可以将算法分为内部排序和外部排序。