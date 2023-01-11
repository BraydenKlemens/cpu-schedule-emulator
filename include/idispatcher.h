#ifndef IDISPATCHER_H
#define IDISPATCHER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
    
//structs for all data used
typedef struct node{
    int process;
    int blocked;
    int running;
    int ready;
}Node;

typedef struct input{
    int time;
    char event[2];
    int process;
    int resource;
}Input;

typedef struct queue{
    int front;
    int rear;
    int size;
    int capacity;
    struct node *data;
}Queue;

typedef struct list{
    struct node data;
    struct list *next;
}List;

Queue *createQueue(int capacity);
int isFull(Queue* queue);
int isEmpty(Queue* queue);
void enqueue(Queue *queue, Node temp);
Node dequeue(Queue *queue);

Node initNode();
void insertNode(List **head, Node toAdd);
List removeNode(List **head, int process);
void printLinkedList(List **head, Node *idle);

void updateAllLists(List **list1, List **list2, List **list3, List **list4, List **list5, int timePassed);
void updateList(List **list, int timePassed);
void updateQueue(Queue *queue, Node *idle, int timePassed);
void insertToList(List **list1, List **list2, List **list3, List **list4, List **list5, Node node, int resource);
Node removeFromList(List **list1, List **list2, List **list3, List **list4, List **list5, int process, int resource);

void freeQueue(Queue *queue);
void freeList(List **list);

#endif