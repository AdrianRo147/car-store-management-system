#include "linked_list.h"
#include "node.h"

#include <stdlib.h>

void InitLinkedList(struct LinkedList* pList, void* pData)
{
  if (pData == NULL)
    pList->stCount = 0;
  else
    pList->stCount = 1;

  pList->pStart = (struct Node*)malloc(sizeof(struct Node));
  pList->pEnd = pList->pStart;

  pList->FindNode = &FindNode;
  pList->GetItemsAsArray = &GetItemsAsArray;

  InitNode(pList->pStart, pData);
}

bool InsertToList(struct LinkedList* pList, void* pData)
{
  struct Node* pNode = Push(pList->pEnd, pData);

  if (pNode == NULL)
    return false;

  pList->pEnd = pNode;
  pList->stCount++;

  return true;
}

bool RemoveFromList(struct LinkedList* pList, struct Node* pTarget)
{
  struct Node* pNode = Pop(pList->pStart, pTarget);

  if (pNode == NULL)
    return false;

  if (pNode->pNext == NULL)
    pList->pEnd = pNode;

  if (pList->pStart->pData == NULL && pList->pStart->pNext != NULL)
  {
    struct Node* pOriginalStart = pList->pStart;
    pList->pStart = pList->pStart->pNext;
    free(pOriginalStart);
    pOriginalStart = NULL;
  }

  pList->stCount--;

  return true;
}

void FreeLinkedList(struct LinkedList* pList)
{
  FreeNodes(pList->pStart);
  pList->pStart = NULL;
  pList->pEnd = NULL;
  free(pList);
}
