#ifndef NODE_H
#define NODE_H

#include <stdio.h>

struct Node
{
  void* pData;
  struct Node* pNext;
};

extern void InitNode(struct Node* pNode, void* pData);
extern struct Node* Push(struct Node* pLast, void* pData);
extern struct Node* Pop(struct Node* pStart, struct Node* pTarget);
extern struct Node* FindNode(struct Node* pStart, void* pData);
extern void FreeNodes(struct Node* pStart);
extern void GetItemsAsArray(struct Node* pStart, void** ppDst, size_t stArraySize);

#endif
