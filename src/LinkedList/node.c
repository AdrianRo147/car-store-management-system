#include "node.h"

#include <stdlib.h>

void InitNode(struct Node* pNode, void* pData)
{
  pNode->pData = pData;
  pNode->pNext = NULL;
}

struct Node* Push(struct Node* pLast, void* pData)
{
  if (pLast == NULL || pData == NULL)
    return NULL;

  if (pLast->pData == NULL)
  {
    pLast->pData = pData;
    return pLast;
  }

  struct Node* pNew = (struct Node*)malloc(sizeof(struct Node));
  pNew->pData = pData;
  pNew->pNext = NULL;

  pLast->pNext = pNew;

  return pNew;
}

struct Node* Pop(struct Node* pStart, struct Node* pTarget) {
  if (pTarget == NULL || (pStart->pData == NULL && pStart->pNext == NULL))
    return NULL;

  struct Node* pPrevious = NULL;
  struct Node* pCurrent = pStart;

  if (pStart == pTarget)
  {
    free(pCurrent->pData);
    pCurrent->pData = NULL;

    return pCurrent;
  }

  while (pCurrent != NULL)
  {
    struct Node* pNext = pCurrent->pNext;

    if (pCurrent == pTarget)
    {
      free(pCurrent->pData);
      pCurrent->pData = NULL;

      free(pCurrent);
      pCurrent = NULL;

      if (pPrevious != NULL)
        pPrevious->pNext = pNext;

      return pPrevious;
    }

    pPrevious = pCurrent;
    pCurrent = pNext;
  }

  return NULL;
}

struct Node* FindNode(struct Node* pStart, void* pData)
{
  if (pStart == NULL || pData == NULL)
    return NULL;

  struct Node* pCurrent = pStart;

  while (pCurrent != NULL)
  {
    if (pCurrent->pData == pData)
      return pCurrent;

    pCurrent = pCurrent->pNext;
  }

  return NULL;
}

void FreeNodes(struct Node* pStart)
{
  if (pStart == NULL)
    return;

  struct Node* pCurrent = pStart;
  struct Node* pNext;

  while (pCurrent != NULL)
  {
    pNext = pCurrent->pNext;

    if (pCurrent->pData != NULL)
    {
      free(pCurrent->pData);
      pCurrent->pData = NULL;
    }

    free(pCurrent);

    pCurrent = pNext;
  }
}

void GetItemsAsArray(struct Node* pStart, void** ppDst, size_t stArraySize)
{
  if (pStart == NULL || ppDst == NULL || stArraySize < 1)
    return;

  size_t i = 0;
  const struct Node* pCurrent = pStart;

  while (pCurrent != NULL && i < stArraySize)
  {
    if (pCurrent->pData == NULL && pCurrent->pNext != NULL)
    {
      struct Node* pNext = pCurrent->pNext;
      pCurrent = pNext;
      continue;
    }

    struct Node* pNext = pCurrent->pNext;
    *(ppDst + i) = pCurrent->pData;
    pCurrent = pNext;
    i++;
  }
}
