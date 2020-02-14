# 结构操作

## output_search(l, real_ind);

1. 要求：如果插入或删除成功一个元素，则在输出链表时这个元素位置的下面有个箭头，如果插入或删除失败，则在head下面有个箭头。

2. 思路：

   1. 很明显，就是输出多少个“ ”的问题。
   2. 再细想一下，就是如何定位这个位置(包含成功与失败)。
   3. 其实定位很简单，只需要判断一下是否插入或删除成功就行，最后real_ind = flag ? ind : 0;
   4. 定位之后要解决的问题就是输出多少个空格怎么计算？
      + 一开始我比较low，就是直接估算。。。。。(太low了。。)
      + 庆龙和泽哥就比较NB了，利用printf家族的返回值：向标准输出打印的字符个数 来计算空格

3. Bug：

   如果删除了最后一个元素，那么再要定位到那个位置时会指向NULL后面， 属于非法访问，所以得改，

   这样如果删除最后一个元素，可以令箭头指向NULL(这属于特殊情况)。

4. 终极代码：

   ```C
   void output_search(LinkedList *l, int ind) {
       char str[100];
       int offset = 3;
       ListNode *p = l->head.next;
       while (ind != -1 && p) {//这个的p是解决段错误的关键！！！
           offset += sprintf(str, "%d->", p->data);
           ind -= 1;
           p = p->next;
       }
       if (!p && ind != -1) offset += 3;//如果是最后一个元素被erase，就指向NULL；
       for (int i = 0; i < offset; i++) printf(" ");
       printf("^\n");
       for (int i = 0; i < offset; i++) printf(" ");
       printf("|\n\n");
       return;
   }
   ```

   

5. 启示：

   只有在真正实现一个功能/做项目时才能让思维能力和代码理解有质的提升！