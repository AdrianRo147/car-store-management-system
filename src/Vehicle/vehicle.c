#include "vehicle.h"
#include "../Customer/customer.h"
#include "../Utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Employee/employee.h"

struct LinkedList* pVehiclesList = NULL;

void InitVehicle(struct Vehicle* pVehicle)
{
  pVehiclesList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
  InitLinkedList(pVehiclesList, pVehicle);
}

bool IsVinDuplicate(char* szVin)
{
  const size_t stVehiclesCount = pVehiclesList->stCount;
  void** ppVehicles = (void**)malloc(stVehiclesCount * sizeof(void*));
  pVehiclesList->GetItemsAsArray(pVehiclesList->pStart, ppVehicles, stVehiclesCount);

  for (size_t i = 0; i < stVehiclesCount; i++)
  {
    const struct Vehicle* pVehicle = (struct Vehicle*)*(ppVehicles + i);

    if (!strcmp(pVehicle->szVin, szVin))
    {
      free(ppVehicles);
      ppVehicles = NULL;
      return true;
    }
  }

  free(ppVehicles);
  ppVehicles = NULL;

  return false;
}

void AddVehicle(char* szManufacturer, char* szModel, char* szVin, struct Date ManufactionDate, unsigned int iKilometersDriven)
{
  unsigned short sId;

  if (pVehiclesList->pStart->pData == NULL)
  {
    sId = 0;
  }
  else
  {
    const struct Vehicle* pLast = (struct Vehicle*)pVehiclesList->pEnd->pData;
    sId = pLast->sId + 1;
  }

  struct Vehicle* pNew = (struct Vehicle*)malloc(sizeof(struct Vehicle));

  pNew->sId = sId;
  StringCopy(szManufacturer, pNew->szManufacturer, sizeof(pNew->szManufacturer));
  StringCopy(szModel, pNew->szModel, sizeof(pNew->szModel));
  StringCopy(szVin, pNew->szVin, sizeof(pNew->szVin));
  pNew->ManufactionDate = ManufactionDate;
  pNew->iKilometersDriven = iKilometersDriven;
  SetCurrentDate(&pNew->dateCreatedAt);
  pNew->bWasSold = false;
  pNew->sCustomerId = (unsigned short)-1;
  pNew->sEmployeeId = (unsigned short)-1;
  InitDate(&pNew->dateSoldAt, 0, 0, 0);

  const bool bPushResult = InsertToList(pVehiclesList, (void*)pNew);

  if (!bPushResult)
    perror("Failed to add vehicle!\n");
}

void RemoveVehicle(struct Vehicle* pVehicle)
{
  if (pVehicle->bWasSold)
  {
    if (!RevertVehicleSale(pVehicle))
    {
      perror("Failed to remove vehicle, database might be corrupted!\n");
      return;
    }
  }

  struct Node* pTarget = pVehiclesList->FindNode(pVehiclesList->pStart, (void*)pVehicle);

  const bool bPopResult = RemoveFromList(pVehiclesList, pTarget);

  if (!bPopResult)
    perror("Failed to remove vehicle!\n");
}

void UpdateVehicle(struct Vehicle* pVehicle, char* szManufacturer, char* szModel, char* szVin, struct Date ManufactionDate, unsigned int iKilometersDriven)
{
  if (strcmp(szManufacturer, "."))
    StringCopy(szManufacturer, pVehicle->szManufacturer, sizeof(pVehicle->szManufacturer));

  if (strcmp(szModel, "."))
    StringCopy(szModel, pVehicle->szModel, sizeof(pVehicle->szModel));

  if (strcmp(szVin, "."))
    StringCopy(szVin, pVehicle->szVin, sizeof(pVehicle->szVin));

  if (!IsNullDate(ManufactionDate))
    pVehicle->ManufactionDate = ManufactionDate;

  if (iKilometersDriven != (unsigned int)-1)
    pVehicle->iKilometersDriven = iKilometersDriven;
}

bool GetVehicle(unsigned short sId, struct Vehicle** ppVehicle)
{
  const size_t stVehiclesCount = pVehiclesList->stCount;

  if (stVehiclesCount == 0)
    return false;

  void** pVehicles = malloc(stVehiclesCount * sizeof(void*));
  pVehiclesList->GetItemsAsArray(pVehiclesList->pStart, pVehicles, stVehiclesCount);

  for (size_t i = 0; i < stVehiclesCount; i++)
  {
    if (((struct Vehicle*)*(pVehicles + i))->sId == sId)
    {
      *ppVehicle = (struct Vehicle*)*(pVehicles + i);
      free(pVehicles);
      pVehicles = NULL;

      return true;
    }
  }

  free(pVehicles);
  pVehicles = NULL;

  return false;
}

void PrintAllVehicles()
{
  const size_t stVehiclesCount = pVehiclesList->stCount;

  if (stVehiclesCount == 0)
  {
    printf("No vehicles found\n\n");
    return;
  }

  void** ppVehicles = malloc(stVehiclesCount * sizeof(void*));
  pVehiclesList->GetItemsAsArray(pVehiclesList->pStart, ppVehicles, stVehiclesCount);

  for (void** i = ppVehicles; i < ppVehicles + stVehiclesCount; i++)
  {
    PrintVehicle(*(struct Vehicle**)i);
  }

  free(ppVehicles);
  ppVehicles = NULL;
}

void PrintVehicle(struct Vehicle* pVehicle)
{
  if (pVehicle == NULL)
    return;

  char szManufactionDate[13] = { 0 };
  FormatDate(pVehicle->ManufactionDate, szManufactionDate);

  char szCreatedAt[13] = { 0 };
  FormatDate(pVehicle->dateCreatedAt, szCreatedAt);

  printf("Vehicle #%d\n", pVehicle->sId);
  printf("Manufacturer: %s\n", pVehicle->szManufacturer);
  printf("Model: %s\n", pVehicle->szModel);
  printf("VIN: %s\n", pVehicle->szVin);
  printf("Manufaction date: %s\n", szManufactionDate);
  printf("Kilometers driven: %d\n", pVehicle->iKilometersDriven);
  printf("Created at: %s\n", szCreatedAt);

  if (pVehicle->bWasSold)
  {
    printf("\n");

    struct Customer* pCustomer;

    if (!GetCustomer(pVehicle->sCustomerId, &pCustomer))
    {
      printf("Error occured while getting customer informations, database might be corrupted!\n\n");
      return;
    }

    struct Employee* pEmployee;

    if (!GetEmployee(pVehicle->sEmployeeId, &pEmployee))
    {
      printf("Error occured while getting customer informations, database might be corrupted!\n\n");
      return;
    }

    char szSoldAt[13] = { 0 };
    FormatDate(pVehicle->dateSoldAt, szSoldAt);

    printf("Sold at %s\n", szSoldAt);

    printf("Sold by %s %s [ID: %d]\n", pEmployee->szFirstName, pEmployee->szSurname, pEmployee->sId);
    printf("Sold to %s %s [ID: %d]\n", pCustomer->szFirstName, pCustomer->szSurname, pCustomer->sId);
  }
  else
  {
    printf("Vehicle is available to be sold\n");
  }

  printf("\n");
}

bool SellVehicle(struct Vehicle* pVehicle, struct Customer* pCustomer, struct Employee* pEmployee)
{
  unsigned short* pCustomerVehicleId = malloc(sizeof(unsigned short));
  *pCustomerVehicleId = pVehicle->sId;

  unsigned short* pEmployeeVehicleId = malloc(sizeof(unsigned short));
  *pEmployeeVehicleId = pVehicle->sId;

  if (!InsertToList(pCustomer->pBoughtVehiclesList, (void*)pCustomerVehicleId) || !InsertToList(pEmployee->pSoldVehiclesList, (void*)pEmployeeVehicleId))
    return false;

  pVehicle->bWasSold = true;
  pVehicle->sCustomerId = pCustomer->sId;
  pVehicle->sEmployeeId = pEmployee->sId;
  SetCurrentDate(&pVehicle->dateSoldAt);

  return true;
}

bool RevertVehicleSale(struct Vehicle* pVehicle)
{
  if (pVehicle == NULL)
    return false;

  if (!pVehicle->bWasSold)
    return false;

  struct Customer* pCustomer = NULL;

  if (!GetCustomer(pVehicle->sCustomerId, &pCustomer))
    return false;

  const size_t stBoughtVehiclesCount = pCustomer->pBoughtVehiclesList->stCount;
  void** ppBoughtVehiclesList = (void**)malloc(sizeof(void*) * stBoughtVehiclesCount);
  pCustomer->pBoughtVehiclesList->GetItemsAsArray(pCustomer->pBoughtVehiclesList->pStart, ppBoughtVehiclesList, stBoughtVehiclesCount);

  for (void** i = ppBoughtVehiclesList; i < ppBoughtVehiclesList + stBoughtVehiclesCount; i++)
  {
    unsigned short* sId = (unsigned short*)*i;

    if (sId == NULL)
    {
      free(ppBoughtVehiclesList);
      ppBoughtVehiclesList = NULL;

      return false;
    }

    if (*sId == pVehicle->sId)
    {
      struct Node* pFoundNode = pCustomer->pBoughtVehiclesList->FindNode(pCustomer->pBoughtVehiclesList->pStart, (void*)sId);

      if (pFoundNode == NULL)
      {
        free(ppBoughtVehiclesList);
        ppBoughtVehiclesList = NULL;

        return false;
      }

      const bool bPopResult = RemoveFromList(pCustomer->pBoughtVehiclesList, pFoundNode);

      if (!bPopResult)
      {
        free(ppBoughtVehiclesList);
        ppBoughtVehiclesList = NULL;

        return false;
      }

      pVehicle->sCustomerId = (unsigned short)-1;

      break;
    }
  }

  free(ppBoughtVehiclesList);
  ppBoughtVehiclesList = NULL;

  struct Employee* pEmployee = NULL;

  if (!GetEmployee(pVehicle->sEmployeeId, &pEmployee))
    return false;

  const size_t stSoldVehiclesCount = pEmployee->pSoldVehiclesList->stCount;
  void** ppSoldVehiclesList = (void**)malloc(sizeof(void*) * stSoldVehiclesCount);
  pEmployee->pSoldVehiclesList->GetItemsAsArray(pEmployee->pSoldVehiclesList->pStart, ppSoldVehiclesList, stSoldVehiclesCount);

  for (void** i = ppSoldVehiclesList; i < ppSoldVehiclesList + stSoldVehiclesCount; i++)
  {
    unsigned short* sId = (unsigned short*)*i;

    if (sId == NULL)
    {
      free(ppSoldVehiclesList);
      ppSoldVehiclesList = NULL;

      return false;
    }

    if (*sId == pVehicle->sId)
    {
      struct Node* pFoundNode = pEmployee->pSoldVehiclesList->FindNode(pEmployee->pSoldVehiclesList->pStart, (void*)sId);

      if (pFoundNode == NULL)
      {
        free(ppSoldVehiclesList);
        ppSoldVehiclesList = NULL;

        return false;
      }

      const bool bPopResult = RemoveFromList(pEmployee->pSoldVehiclesList, pFoundNode);

      if (!bPopResult)
      {
        free(ppSoldVehiclesList);
        ppSoldVehiclesList = NULL;

        return false;
      }

      pVehicle->sEmployeeId = (unsigned short)-1;

      break;
    }
  }

  free(ppSoldVehiclesList);
  ppSoldVehiclesList = NULL;

  if (pVehicle->sCustomerId == (unsigned short)-1 && pVehicle->sEmployeeId == (unsigned short)-1)
    pVehicle->bWasSold = false;
  else
    return false;

  return true;
}

void FreeVehicles()
{
  FreeLinkedList(pVehiclesList);
  pVehiclesList = NULL;
}
