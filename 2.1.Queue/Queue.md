# 结构操作

## expand(q)

### 我的idea(在原来realloc的基础上更改)

1. 顺序结构实现扩容很简单，所以要思考的就是如何处理扩容后的元素顺序(特指tail在head前的情况)

2. 思路：

   1. 一开始我想的是把整个原来的循环队列变成顺序的也就是tail在head后的，比如3 1 2 变成 1 2 3

      这样的话比较难实现，确切地说是有bug，首先这肯定涉及到要有一个空间来存储0~tail的元素或者head~q->size的元素，但空间不一定够，如果想拿后面扩容的空间来存的话，后面扩容的空间还不知道够不够，所以有bug，那更别提再malloc空间了，所以这个想法就gg了。

      后来在整理笔记时想到可以利用三个reverse来达成这个idea，于是果断写了一下，发现确实可以！！

      代码如下

      ```C
      void reverse(Queue *q, int begin, int end) {
          if (!q) return ;
          while (begin < end) {
              int temp = q->data[begin];
              q->data[begin] = q->data[end];
              q->data[end] = temp;
              ++begin;
              --end;
          }
          return;
      }
      
      
      int expand(Queue *q) {
          if (!q) return 0;
          int extra_size = q->size;
          int *p;
          while (extra_size) {
              p = (int *)realloc(q->data, sizeof(int) * (extra_size + q->size));
              if (p) break;
              extra_size /= 2;
          }
          if (!p) return 0;
          q->data = p;
          q->size += extra_size;
          if (q->head < q->tail) return 1;//如果是正常顺序
          //非正常顺序
          reverse(q, 0, q->tail - 1);
          reverse(q, q->head, q->length - 1);
          reverse(q, 0, q->length - 1);//这三行代码是精髓！！！！！思想来自计蒜客数据结构的“顺序表的循环左移”！！！！！！！！！！！！！！！！
          q->head = 0;
          q->tail = q->length;
          return 1;
      }
      ```

      

   2. 后来想到可以将head~q->size的元素往后移到不能移为止，这样就不用考虑扩容空间多少的问题了。

      + 关于这个idea，我一开始想的是像顺序表的insert操作那样一个一个移动，最后写出来3个for循环嵌套的代码。。。果断放弃。

      + 后来想到可以直接移到相应位置，不用一个一个挪！！！这样只用一个for循环！

      + 代码如下

        ```c
        
        int expand(Queue *q) {
            if (!q) return 0;
            int extra_size = q->size;
            int *p;
            while (extra_size) {
                p = (int *)realloc(q->data, sizeof(int) * (extra_size + q->size));
                if (p) break;
                extra_size /= 2;
            }
            if (!p) return 0;
            q->data = p;
            int previous_size = q->size;
            q->size += extra_size;
            if (q->head < q->tail) return 1;//如果是正常顺序
            //非正常顺序
            /*
            for (int i = 0; i < extra_size; i++) {
                int ind = previous_size;
                for (int j = ind; j < q->size; j++) {
                    for (int k = j; k > q->head; k--) {
                        q->data[k] = q->data[k - 1];
                        q->head++;
                    }
                }
            }
            */
            int ind = q->size - 1;
            for (int i = previous_size - 1; i >= q->head; i--) {
                q->data[ind--] = q->data[i];
            }
            q->head += extra_size;
            return 1;
        }
        ```

        

### 泽哥的idea(放弃realloc改用malloc)

1. 泽哥的想法就是和我原来的想法一致，以head到tail从小到大的正确的顺序把数据输入到新的内存中，但这样就必须要重开辟一片空间，这样就有个bug，可能内存会不够，开辟不了(realloc是在原来的存储区域后面先找看看有没有空间，而malloc是重新找空间)。
2. 代码如下：

```C
int expand(Queue *q) {
  int extra_size = q->size;
  int *p;
  while (extra_size) {
    p = (int *)malloc(sizeof(int) * (extra_size + q->size));
    if (p) break;
    extra_size /= 2;
  }
  if (!p) return 0;
  //下面开始调整顺序，移到新开辟的空间中
  for (int i = q->head, j = 0; j < q->length; j++) {
    p[j] = q->data[(i + j) % q->size];
  }
  q->size += extra_size;
  free(q->data);
  q->data = p;
  q->head = 0;
  q->tail = q->length;
  return 1;
}
```

