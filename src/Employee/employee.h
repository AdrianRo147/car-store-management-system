#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "../LinkedList/linked_list.h"
#include "../Date/date.h"

struct Employee
{
  unsigned short sId;
  char szFirstName[101];
  char szSurname[101];
  struct Date DateOfBirth;
  struct Date dateEmployedUntil;
  struct Date dateCreatedAt;
  struct LinkedList* pSoldVehiclesList; // save unsigned shorts of vehicle IDs
};

extern struct LinkedList* pEmployeesList;

extern void InitEmployees(struct Employee* pEmployee);
extern void AddEmployee(char* szFirstName, char* szSurname, struct Date DateOfBirth, struct Date dateEmployedUntil);
extern void RemoveEmployee(struct Employee* pEmployee);
extern void UpdateEmployee(struct Employee* pEmployee, char* szFirstName, char* szSurname, struct Date DateOfBirth, struct Date dateEmployedUntil);
extern bool GetEmployee(unsigned short sId, struct Employee** ppEmployee);
extern void PrintAllEmployees();
extern void PrintEmployee(struct Employee* pEmployee);
extern void FreeEmployees();

#endif
