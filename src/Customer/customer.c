#include "customer.h"
#include "../Utils/utils.h"
#include "../Employee/employee.h"
#include "../Vehicle/vehicle.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct LinkedList* pCustomersList = NULL;

void InitCustomers(struct Customer* pCustomer)
{
  pCustomersList = malloc(sizeof(struct LinkedList));
  InitLinkedList(pCustomersList, pCustomer);
}

void AddCustomer(char* szFirstName, char* szSurname, struct Date DateOfBirth)
{
  unsigned short sId;

  if (pCustomersList->pStart->pData == NULL)
  {
    sId = 0;
  }
  else
  {
    const struct Node* const pLastNode = pCustomersList->pEnd;
    const struct Customer* const pLastCustomer = (struct Customer*)pLastNode->pData;
    sId = pLastCustomer->sId + 1;
  }

  struct Customer* pNew = (struct Customer*)malloc(sizeof(struct Customer));

  pNew->sId = sId;
  StringCopy(szFirstName, pNew->szFirstName, sizeof(pNew->szFirstName));
  StringCopy(szSurname, pNew->szSurname, sizeof(pNew->szSurname));
  pNew->DateOfBirth = DateOfBirth;
  SetCurrentDate(&pNew->dateCreatedAt);
  pNew->pBoughtVehiclesList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
  InitLinkedList(pNew->pBoughtVehiclesList, NULL);

  const bool bPushResult = InsertToList(pCustomersList, (void*)pNew);

  if (!bPushResult)
    perror("Failed to add customer!\n");
}

void RemoveCustomer(struct Customer* pCustomer)
{
  if (pCustomer->pBoughtVehiclesList->stCount > 0)
  {
    size_t stBoughtVehiclesCount = pCustomer->pBoughtVehiclesList->stCount;
    void** ppBoughtVehiclesList = (void**)malloc(stBoughtVehiclesCount * sizeof(void*));
    pCustomer->pBoughtVehiclesList->GetItemsAsArray(pCustomer->pBoughtVehiclesList->pStart, ppBoughtVehiclesList, stBoughtVehiclesCount);

    for (size_t i = 0; i < stBoughtVehiclesCount; i++)
    {
      unsigned short* sBoughtVehicleId = (unsigned short*)*(ppBoughtVehiclesList + i);

      struct Vehicle* pVehicle = NULL;

      if (!GetVehicle(*sBoughtVehicleId, &pVehicle) || !pVehicle->bWasSold || pVehicle->sCustomerId != pCustomer->sId)
      {
        free(ppBoughtVehiclesList);
        ppBoughtVehiclesList = NULL;

        perror("Failed to remove customer, database might be corrupted!\n");

        return;
      }

      if (!RevertVehicleSale(pVehicle))
      {
        free(ppBoughtVehiclesList);
        ppBoughtVehiclesList = NULL;

        perror("Failed to remove customer, database might be corrupted!\n");

        return;
      }
    }

    free(ppBoughtVehiclesList);
    ppBoughtVehiclesList = NULL;
  }

  if (pCustomer->pBoughtVehiclesList->stCount != 0)
  {
    perror("Failed to remove customer, database might be corrupted!\n");
    return;
  }

  struct Node* pCustomerNode = pCustomersList->FindNode(pCustomersList->pStart, (void*)pCustomer);
  struct LinkedList* pBoughtVehiclesList = ((struct Customer*)pCustomerNode->pData)->pBoughtVehiclesList;

  FreeLinkedList(pBoughtVehiclesList);

  const bool bPopResult = RemoveFromList(pCustomersList, pCustomerNode);

  if (!bPopResult)
    perror("Failed to remove customer!\n");
}

void UpdateCustomer(struct Customer* pCustomer, char* szFirstName, char* szSurname, struct Date DateOfBirth)
{
  if (strcmp(szFirstName, "."))
    StringCopy(szFirstName, pCustomer->szFirstName, sizeof(pCustomer->szFirstName));

  if (strcmp(szSurname, "."))
    StringCopy(szSurname, pCustomer->szSurname, sizeof(pCustomer->szSurname));

  if (!IsNullDate(DateOfBirth))
    pCustomer->DateOfBirth = DateOfBirth;
}

bool GetCustomer(unsigned short sId, struct Customer** ppCustomer)
{
  const size_t stCustomersCount = pCustomersList->stCount;

  if (stCustomersCount == 0)
    return false;

  void** ppCustomers = (void**)malloc(stCustomersCount * sizeof(void*));
  pCustomersList->GetItemsAsArray(pCustomersList->pStart, ppCustomers, stCustomersCount);

  for (void** i = ppCustomers; i < ppCustomers + stCustomersCount; i++)
  {
    struct Customer* pFoundCustomer = (struct Customer*)*i;

    if (pFoundCustomer->sId == sId)
    {
      *ppCustomer = pFoundCustomer;
      free(ppCustomers);
      ppCustomers = NULL;

      return true;
    }
  }

  free(ppCustomers);
  ppCustomers = NULL;

  return false;
}

void PrintAllCustomers()
{
  const size_t stCustomersCount = pCustomersList->stCount;

  if (stCustomersCount == 0)
  {
    printf("No customers found\n\n");
    return;
  }

  void** ppCustomers = malloc(stCustomersCount * sizeof(void*));
  pCustomersList->GetItemsAsArray(pCustomersList->pStart, ppCustomers, stCustomersCount);

  for (void** i = ppCustomers; i < ppCustomers + stCustomersCount; i++)
  {
    PrintCustomer((struct Customer*)*i);
  }

  free(ppCustomers);
  ppCustomers = NULL;
}

void PrintCustomer(struct Customer *pCustomer)
{
  if (pCustomer == NULL)
    return;

  char szDateOfBirth[13] = { 0 };
  FormatDate(pCustomer->DateOfBirth, szDateOfBirth);

  char szCreatedAt[13] = { 0 };
  FormatDate(pCustomer->dateCreatedAt, szCreatedAt);

  printf("Customer #%d\n", pCustomer->sId);
  printf("Name: %s %s\n", pCustomer->szFirstName, pCustomer->szSurname);
  printf("Date of Birth: %s\n", szDateOfBirth);
  printf("Created at: %s\n", szCreatedAt);

  const size_t stVehiclesCount = pCustomer->pBoughtVehiclesList->stCount;

  if (stVehiclesCount == 0)
  {
    printf("Customer didn't bought any vehicles\n\n");
  }
  else
  {
    printf("\n");

    void** ppBoughtVehicles = malloc(stVehiclesCount * sizeof(void*));
    pCustomer->pBoughtVehiclesList->GetItemsAsArray(pCustomer->pBoughtVehiclesList->pStart, ppBoughtVehicles, stVehiclesCount);

    for (void** i = ppBoughtVehicles; i < ppBoughtVehicles + stVehiclesCount; i++)
    {
      unsigned short sId = **(unsigned short**)i;
      struct Vehicle* pVehicle = NULL;

      if (!GetVehicle(sId, &pVehicle))
      {
        free(ppBoughtVehicles);
        ppBoughtVehicles = NULL;

        perror("Failed to get vehicle, database might be corrupted!\n");

        return;
      }

      char szBoughtAt[13] = { 0 };
      FormatDate(pVehicle->dateSoldAt, szBoughtAt);

      printf("%s %s [VIN: %s]\n", pVehicle->szManufacturer, pVehicle->szModel, pVehicle->szVin);
      printf("Bought at %s\n", szBoughtAt);

      struct Employee* pSoldBy = NULL;

      if (!GetEmployee(pVehicle->sEmployeeId, &pSoldBy))
      {
        free(ppBoughtVehicles);
        ppBoughtVehicles = NULL;

        perror("Failed to get employee, database might be corrupted!\n");

        return;
      }

      printf("Sold by %s %s [ID: %d]\n\n", pSoldBy->szFirstName, pSoldBy->szSurname, pSoldBy->sId);
    }

    free(ppBoughtVehicles);
    ppBoughtVehicles = NULL;
  }
}

void FreeCustomers()
{
  void** ppCustomers = (void**)malloc(pCustomersList->stCount * sizeof(void*));
  pCustomersList->GetItemsAsArray(pCustomersList->pStart, ppCustomers, pCustomersList->stCount);

  for (void** i = ppCustomers; i < ppCustomers + pCustomersList->stCount; i++)
  {
    FreeLinkedList((*(struct Customer**)i)->pBoughtVehiclesList);
  }

  FreeLinkedList(pCustomersList);

  free(ppCustomers);
  ppCustomers = NULL;

  pCustomersList = NULL;
}
