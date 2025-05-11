#include "employee.h"

#include "../Utils/utils.h"
#include "../Vehicle/vehicle.h"
#include "../Customer/customer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkedList* pEmployeesList = NULL;

void InitEmployees(struct Employee* pEmployee)
{
  pEmployeesList = malloc(sizeof(struct LinkedList));
  InitLinkedList(pEmployeesList, pEmployee);
}

void AddEmployee(char* szFirstName, char* szSurname, struct Date DateOfBirth, struct Date dateEmployedUntil)
{
  unsigned short sId;

  if (pEmployeesList->pStart->pData == NULL)
  {
    sId = 0;
  }
  else
  {
    const struct Node* const pLastNode = pEmployeesList->pEnd;
    const struct Employee* const pLastEmployee = (struct Employee*)pLastNode->pData;
    sId = pLastEmployee->sId + 1;
  }

  struct Employee* pNew = (struct Employee*)malloc(sizeof(struct Employee));

  pNew->sId = sId;
  StringCopy(szFirstName, pNew->szFirstName, sizeof(pNew->szFirstName));
  StringCopy(szSurname, pNew->szSurname, sizeof(pNew->szSurname));
  pNew->DateOfBirth = DateOfBirth;
  pNew->dateEmployedUntil = dateEmployedUntil;
  SetCurrentDate(&pNew->dateCreatedAt);
  pNew->pSoldVehiclesList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
  InitLinkedList(pNew->pSoldVehiclesList, NULL);

  const bool bPushResult = InsertToList(pEmployeesList, (void*)pNew);

  if (!bPushResult)
    perror("Failed to add employee!\n");
}

void RemoveEmployee(struct Employee* pEmployee)
{
  if (pEmployee->pSoldVehiclesList->stCount > 0)
  {
    const size_t stSoldVehiclesCount = pEmployee->pSoldVehiclesList->stCount;
    void** ppSoldVehicles = (void**)malloc(stSoldVehiclesCount * sizeof(void*));
    pEmployee->pSoldVehiclesList->GetItemsAsArray(pEmployee->pSoldVehiclesList->pStart, ppSoldVehicles, stSoldVehiclesCount);

    for (void** i = ppSoldVehicles; i < ppSoldVehicles + stSoldVehiclesCount; i++)
    {
      unsigned short* sSoldVehicleId = *(unsigned short**)i;

      struct Vehicle* pVehicle = NULL;

      if (!GetVehicle(*sSoldVehicleId, &pVehicle))
      {
        free(ppSoldVehicles);
        ppSoldVehicles = NULL;

        perror("Failed to remove employee, database might be corrupted!\n");

        return;
      }

      if (!RevertVehicleSale(pVehicle))
      {
        free(ppSoldVehicles);
        ppSoldVehicles = NULL;

        perror("Failed to remove employee, database might be corrupted!\n");

        return;
      }
    }

    free(ppSoldVehicles);
    ppSoldVehicles = NULL;
  }

  if (pEmployee->pSoldVehiclesList->stCount != 0)
  {
    perror("Failed to remove employee, database might be corrupted!\n");
    return;
  }

  struct Node* pEmployeeNode = pEmployeesList->FindNode(pEmployeesList->pStart, (void*)pEmployee);
  struct LinkedList* pSoldVehiclesList = ((struct Employee*)pEmployeeNode->pData)->pSoldVehiclesList;

  FreeLinkedList(pSoldVehiclesList);

  const bool bPopResult = RemoveFromList(pEmployeesList, pEmployeeNode);

  if (!bPopResult)
    perror("Failed to remove employee!\n");
}

void UpdateEmployee(struct Employee* pEmployee, char* szFirstName, char* szSurname, struct Date DateOfBirth, struct Date dateEmployedUntil)
{
  if (strcmp(szFirstName, "."))
    StringCopy(szFirstName, pEmployee->szFirstName, sizeof(pEmployee->szFirstName));

  if (strcmp(szSurname, "."))
    StringCopy(szSurname, pEmployee->szSurname, sizeof(pEmployee->szSurname));

  if (!IsNullDate(DateOfBirth))
    pEmployee->DateOfBirth = DateOfBirth;

  if (!IsNullDate(dateEmployedUntil))
    pEmployee->dateEmployedUntil = dateEmployedUntil;
}

bool GetEmployee(unsigned short sId, struct Employee** ppEmployee)
{
  const size_t stEmployeesCount = pEmployeesList->stCount;

  if (stEmployeesCount == 0)
    return false;

  void** ppEmployees = (void**)malloc(stEmployeesCount * sizeof(void*));
  pEmployeesList->GetItemsAsArray(pEmployeesList->pStart, ppEmployees, stEmployeesCount);

  for (void** i = ppEmployees; i < ppEmployees + stEmployeesCount; i++)
  {
    struct Employee* pFoundEmployee = *(struct Employee**)i;

    if (pFoundEmployee->sId == sId)
    {
      *ppEmployee = pFoundEmployee;
      free(ppEmployees);
      ppEmployees = NULL;

      return true;
    }
  }

  free(ppEmployees);
  ppEmployees = NULL;

  return false;
}

void PrintAllEmployees()
{
  const size_t stEmployeesCount = pEmployeesList->stCount;

  if (stEmployeesCount == 0)
  {
    printf("No employees found\n");
    return;
  }

  void** ppEmployees = (void**)malloc(stEmployeesCount * sizeof(void*));
  pEmployeesList->GetItemsAsArray(pEmployeesList->pStart, ppEmployees, stEmployeesCount);

  for (void** i = ppEmployees; i < ppEmployees + stEmployeesCount; i++)
  {
    PrintEmployee(*(struct Employee**)i);
  }

  free(ppEmployees);
  ppEmployees = NULL;
}

void PrintEmployee(struct Employee* pEmployee)
{
  if (pEmployee == NULL)
    return;

  char szDateOfBirth[13] = { 0 };
  FormatDate(pEmployee->DateOfBirth, szDateOfBirth);

  char szEmployedUntil[13] = { 0 };
  FormatDate(pEmployee->dateEmployedUntil, szEmployedUntil);

  char szCreatedAt[13] = { 0 };
  FormatDate(pEmployee->dateCreatedAt, szCreatedAt);

  printf("Employee #%d\n", pEmployee->sId);
  printf("Name: %s %s\n", pEmployee->szFirstName, pEmployee->szSurname);
  printf("Date of Birth: %s\n", szDateOfBirth);
  printf("Employed Until: %s\n", szEmployedUntil);
  printf("Created at: %s\n", szCreatedAt);

  const size_t stVehiclesCount = pEmployee->pSoldVehiclesList->stCount;

  if (stVehiclesCount == 0)
  {
    printf("Employee didn't sold any vehicle\n\n");
  }
  else
  {
    printf("\n");

    void** ppSoldVehicles = (void**)malloc(stVehiclesCount * sizeof(void*));
    pEmployee->pSoldVehiclesList->GetItemsAsArray(pEmployee->pSoldVehiclesList->pStart, ppSoldVehicles, stVehiclesCount);

    for (void** i = ppSoldVehicles; i < ppSoldVehicles + stVehiclesCount; i++)
    {
      unsigned short sId = **(int**)i;
      struct Vehicle* pVehicle = NULL;

      if (!GetVehicle(sId, &pVehicle))
        perror("Failed to get vehicle, database might be corrupted!\n");

      char szSoldAt[13] = { 0 };
      FormatDate(pVehicle->dateSoldAt, szSoldAt);

      printf("%s %s [VIN: %s]\n", pVehicle->szManufacturer, pVehicle->szModel, pVehicle->szVin);
      printf("Sold at %s\n", szSoldAt);

      struct Customer* pBoughtBy = NULL;

      if (!GetCustomer(pVehicle->sCustomerId, &pBoughtBy))
      {
        free(ppSoldVehicles);
        ppSoldVehicles = NULL;
        perror("Failed to get customer, database might be corrupted!\n");
        return;
      }

      printf("Bought by %s %s [ID: %d]\n\n", pBoughtBy->szFirstName, pBoughtBy->szSurname, pBoughtBy->sId);
    }

    free(ppSoldVehicles);
    ppSoldVehicles = NULL;
  }
}

void FreeEmployees()
{
  void** ppEmployees = (void**)malloc(pEmployeesList->stCount * sizeof(void*));
  pEmployeesList->GetItemsAsArray(pEmployeesList->pStart, ppEmployees, pEmployeesList->stCount);

  for (void** i = ppEmployees; i < ppEmployees + pEmployeesList->stCount; i++)
  {
    FreeLinkedList((*(struct Employee**)i)->pSoldVehiclesList);
  }

  FreeLinkedList(pEmployeesList);

  free(ppEmployees);
  ppEmployees = NULL;

  pEmployeesList = NULL;
}
