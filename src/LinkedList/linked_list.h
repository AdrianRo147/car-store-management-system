#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"

#include <stdbool.h>

struct LinkedList
{
  size_t stCount;
  struct Node* pStart;
  struct Node* pEnd;

  struct Node* (*FindNode)(struct Node*, void*);
  void (*GetItemsAsArray)(struct Node*, void**, size_t);
};

extern void InitLinkedList(struct LinkedList* pList, void* pData);
extern bool InsertToList(struct LinkedList* pList, void* pData);
extern bool RemoveFromList(struct LinkedList* pList, struct Node* pTarget);
extern void FreeLinkedList(struct LinkedList* pList);

#endif
