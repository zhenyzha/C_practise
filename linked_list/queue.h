#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>

typedef int Item;   //用于use_q.c

#define MAXQUEUE 10

typedef struct node
{
    Item item;
    struct node * next;
} Node;

typedef struct queue
{
    Node * front;   //指向队列首项的指针
    Node * rear;    //指向队列尾项的指针
    int items;      //队列中的项数
} Queue;

void InitializeQueue(Queue * pq);   /* 初始化队列，
                                     前置条件：pq 指向一个队列
                                     后置条件：队列被初始化为空 */
bool QueueIsFull(const Queue * pq); //检查队列是否已满

bool QueueIsEmpty(const Queue * pq);

int QueueItemCount(const Queue * pq); //确定队列中的项数

bool EnQueue(Item item, Queue * pq);  //在队列末尾添加项，item将添加在队列末尾

bool DeQueue(Item *pitem, Queue * pq); //在队列开头删除项

void EmptyTheQueue(Queue * pq); //清空队列

#endif
