#ifndef BUDDY_SYSTEM_H
#define BUDDY_SYSTEM_H


#include <stdio.h>
#include <stdlib.h>

struct Node;
struct HeadNode;

struct HeadNode * buddy_new(int size);
struct Node * buddy_alloc(struct HeadNode * avail, int size, int n);
struct Node * buddy(struct Node * p);
void buddy_combine(struct HeadNode * avail, int size, struct Node * p);
void buddy_free(struct HeadNode * avail);
void buddy_print(struct HeadNode * avail, int size);


#endif