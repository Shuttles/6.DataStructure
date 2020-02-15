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



# 循环链表

## 按泽哥讲的实现的一版

1. 一开始想的这个实现起来很容易，毕竟泽哥也讲过，就是尾结点指向头结点并且虚拟头的next永远指向的是尾结点就行了，但是实际操作起来还是挺困难的，clear_LinkedList, insert, erase, output都得大改！

2. 总体思想如1所示即

   + 尾结点的next指向头结点
   + 虚拟头.next指向尾结点(这样是为了还按原来的insert方式插入(即ind--))

3. 总体只需要注意两种特殊情况，一是为空链表即head.next == NULL， 二是只有一个元素时(它的next指向自己)。

4. clear_LinkedList

   代码如下

   ```C
   void clear_LinkedList(LinkedList *l) {
     if (!l) return ;
     ListNode *r = l->head.next, *p = l->head.next, *q;
      p = p ? p->next : NULL;//为了防止链表为空
     while (p != r) {//终止条件必须是p == r!!!因为这是循环链表！！
       q = p->next;
       clear_ListNoe(p);
       p = q;
     }
     if (p) clear_ListNode(p);//如果链表为空，那么p也为空，就不必clear了！！
     free(l);
     return ;
   }
   ```

   PS：写这段代码我其实只考虑了空链表的情况，但是发现对于只有一个元素的情况也成立。

5. insert

   1. 首先考虑如何建成一个循环链表？ 只需要在插入第一个元素之后令它指向自己即可！

   2. 最特殊的情况就是再插入第一个元素之后，因为这个元素既相当于头结点(0号结点)也相当于尾结点。

      为什么呢？

      因为接下来按照普适情况的代码逻辑ind == 0 || ind == 1都可以插入。

      如果ind == 0插入的话，按照普适情况的代码逻辑，虚拟头指向不变，原来的这个元素就是尾结点。

      如果ind == 1插入的话，按照普适情况的代码逻辑，虚拟头结点就得指向新插入的元素(ind == l->length)，这样原来的元素就是头结点。

   3. insert要多考虑的一点是如果插入到尾部，虚拟头结点的指向要移动！！

   代码如下

   ```C
   int insert(LinkedList *l, int ind, int val) {
     ListNode *q = init_ListNode(val);
     //如果链表为空，那么插入的结点就为尾结点！！！(尾结点意味着下一个插入成功的只有ind == 0 || ind == 1)
     if (!l->head.next) {
       if (ind != 0) return 0;//ind必须等于0才能插入
       l->head.next = q;
       q->next = q;//指向自己
       l->length += 1;
       return 1;
     }
     if (ind < 0 || ind > l->length) return 0;
     int ret = ind;//暂存ind信息
     ListNode *p = L->head.next;
     while (ind--) p = p->next;
     q->next = p->next;
     p->next = q;
     if (ret == l->length) l->head.next = q;//如果插入到尾部的话要移动虚拟头的指向！
     l->length += 1;
     return 1;
   }
   ```

6. erase

   1. 这里就不需要考虑空链表了，因为第二个if会自动判断！！！(l->length == 0)
   2. 但这里需要考虑只有一个元素的情况，如果删除了那个元素，l->head.next要指向NULL，否则不知道会指向哪！！！
   3. erase要多考虑的一点是如果删除了尾部元素，虚拟头的next的指向要前移！(也就是指向p)

   代码如下：

   ```C
   int erase(LinkedList *l, int ind) {
     if (!l) return 0;
     if (ind < 0 || ind >= l->length) return 0;
     ListNode *p = l->head.next, *q;
     int ret = ind;//暂存ind信息
     while (ind--) p = p->next;
     q = p->next;
     p->next = q->next;
     clear_ListNode(q);
     if (ret = l->length - 1) l->head.next = p;//如果删除了尾结点，head.next要前移一位！！！
     l->length -= 1;
     if (l->length == 0) l->head.next = NULL;//如果删除了唯一的元素，head.next要指向NULL，否则不知道会指向哪！！
   }
   ```

7. output

   1. 这里不用考虑只有一个元素的情况了！

   2. 为了更好地观察这个循环链表，我输出时最后多输出了一下0号结点的值！

   代码如下

   ```C
   void output(LinkedList *l) {
     if (!l) return ;
     printf("LinkedList(%d) = [", l->length);
     ListNode *p = l->head.next ? l->head.next->next : l->head.next;//如果链表不为空就指向0号结点，为空就指向NULL； 
     int len = l->length;
     while (len--) { //不能像单链表那样用while (p)了！！
       printf("%d->", p->data);
       p = p->next;
     }
     //为显示出循环链表的特点，让0号结点最后也输出！！
     if (l->length != 0) printf("%d]\n", l->head.next->next->data);
     else printf("]\n");
     return ;
   }
   ```

8. 总结

   1. 大方向上，每个结构操作要考虑空链表和只有一个元素的特殊情况。
   2. 小方向上，每个结构操作还有自己的特殊情况。
   3. 首先考虑普适情况，最后调整特殊情况！！！！！！！！！！！！！！！！！！！！！！！！！！！

9. 启示：

   只有在真正实现一个功能/做项目时才能让思维能力和代码理解有质的提升！