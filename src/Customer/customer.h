#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "../Date/date.h"
#include "../LinkedList/linked_list.h"

struct Customer {
  unsigned short sId;
  char szFirstName[101];
  char szSurname[101];
  struct Date DateOfBirth;
  struct Date dateCreatedAt;
  struct LinkedList* pBoughtVehiclesList; // save unsigned short of ids
};

extern struct LinkedList* pCustomersList;

extern void InitCustomers(struct Customer* pCustomer);
extern void AddCustomer(char* szFirstName, char* szSurname, struct Date DateOfBirth);
extern void RemoveCustomer(struct Customer* pCustomer);
extern void UpdateCustomer(struct Customer* pCustomer, char* szFirstName, char* szSurname, struct Date DateOfBirth);
extern bool GetCustomer(unsigned short sId, struct Customer** ppCustomer);
extern void PrintAllCustomers();
extern void PrintCustomer(struct Customer* pCustomer);
extern void FreeCustomers();

#endif
