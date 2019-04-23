/* adlist.h - A generic doubly linked list implementation
 *
 * Copyright (c) 2006-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ADLIST_H__
#define __ADLIST_H__

/* Node, List, and Iterator are the only data structures used currently. */
// 双端链表节点
typedef struct listNode {
    struct listNode *prev; // 前置节点
    struct listNode *next; // 后置节点
    void *value; // 节点的值
} listNode;

// 双端链表迭代器
typedef struct listIter {
    listNode *next; // 当前迭代到的节点
    int direction;  // 迭代的方向
} listIter;

// 双端链表结构
typedef struct list {
    listNode *head;  // 表头节点
    listNode *tail;  // 表尾结点
    void *(*dup)(void *ptr);  // 节点复制函数
    void (*free)(void *ptr);  // 节点释放函数
    int (*match)(void *ptr, void *key);  // 节点值对比函数
    unsigned long len;  // 链表所包含的节点数量
} list;

/* Functions implemented as macros */
// 返回给定链表所包含的节点数量，T=O(1)
#define listLength(l) ((l)->len)
// 返回给定链表的表头节点，T=O(1)
#define listFirst(l) ((l)->head)
// 返回给定链表的表尾结点，T=O(1)
#define listLast(l) ((l)->tail)
// 返回给定节点的前置节点，T=O(1)
#define listPrevNode(n) ((n)->prev)
// 返回给定节点的后置节点，T=O(1)
#define listNextNode(n) ((n)->next)
// 返回给定节点的节点值，T=O(1)
#define listNodeValue(n) ((n)->value)

// 将链表l复制函数的值设置为m，T=O(1)
#define listSetDupMethod(l,m) ((l)->dup = (m))
// 将链表l释放函数的值设置为m，T=O(1)
#define listSetFreeMethod(l,m) ((l)->free = (m))
// 将链表比较函数的值设置为m，T=O(1)
#define listSetMatchMethod(l,m) ((l)->match = (m))

// 返回给定链表的复制函数值，T=O(1)
#define listGetDupMethod(l) ((l)->dup)
// 返回给定链表的释放函数值，T=O(1)
#define listGetFree(l) ((l)->free)
// 返回给定链表的比较函数值，T=O(1)
#define listGetMatchMethod(l) ((l)->match)

/* Prototypes */
// 创建一个不包含任何节点的新链表，T=O(1)
list *listCreate(void);
// 释放给定链表，以及链表中的所有节点，T=O(N)
void listRelease(list *list);
// TODO:
void listEmpty(list *list);
// 将一个包含给定值的新节点添加到给定链表的表头，T=O(1)
list *listAddNodeHead(list *list, void *value);
// 将一个包含给定值的新节点添加到给定链表的表尾，T=O(1)
list *listAddNodeTail(list *list, void *value);
// 将一个包含给定值的新节点添加到给定节点的之前或之后，T=O(1)
list *listInsertNode(list *list, listNode *old_node, void *value, int after);
// 从链表中删除给定节点，T=O(N)
void listDelNode(list *list, listNode *node);
// TODO:
listIter *listGetIterator(list *list, int direction);
// TODO:
listNode *listNext(listIter *iter);
// TODO:
void listReleaseIterator(listIter *iter);
// 复制一个给定链接的副本，T=O(N)
list *listDup(list *orig);
// 查找并返回链表中包含给定值的节点，T=O(N)
listNode *listSearchKey(list *list, void *key);
// 返回链表在给定索引上的节点，T=O(N)
listNode *listIndex(list *list, long index);
// TODO:
void listRewind(list *list, listIter *li);
// TODO:
void listRewindTail(list *list, listIter *li);
// TODO:
void listRotate(list *list);
// TODO:
void listJoin(list *l, list *o);

/* Directions for iterators */
/* 迭代器进行迭代的方向 */
#define AL_START_HEAD 0  // 从表头向表尾进行迭代
#define AL_START_TAIL 1  // 从表尾向表头进行迭代

#endif /* __ADLIST_H__ */
