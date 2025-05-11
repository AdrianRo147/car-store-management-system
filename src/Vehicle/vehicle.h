#ifndef VEHICLE_H
#define VEHICLE_H

#include "../LinkedList/linked_list.h"
#include "../Date/date.h"
#include "../Customer/customer.h"
#include "../Employee/employee.h"

#include <stdbool.h>

struct Vehicle
{
  unsigned short sId;
  char szManufacturer[101];
  char szModel[101];
  char szVin[18];
  struct Date ManufactionDate;
  unsigned int iKilometersDriven;
  struct Date dateCreatedAt;
  bool bWasSold;
  unsigned short sEmployeeId;
  unsigned short sCustomerId;
  struct Date dateSoldAt;
};

extern struct LinkedList* pVehiclesList;

extern void InitVehicle(struct Vehicle* pVehicle);
extern bool IsVinDuplicate(char* szVin);
extern void AddVehicle(char* szManufacturer, char* szModel, char* szVin, struct Date ManufactionDate, unsigned int iKilometersDriven);
extern void RemoveVehicle(struct Vehicle* pVehicle);
extern void UpdateVehicle(struct Vehicle* pVehicle, char* szManufacturer, char* szModel, char* szVin, struct Date ManufactionDate, unsigned int iKilometersDriven);
extern bool GetVehicle(unsigned short sId, struct Vehicle** ppVehicle);
extern void PrintAllVehicles();
extern void PrintVehicle(struct Vehicle* pVehicle);
extern bool SellVehicle(struct Vehicle* pVehicle, struct Customer* pCustomer, struct Employee* pEmployee);
extern bool RevertVehicleSale(struct Vehicle* pVehicle);
extern void FreeVehicles();

#endif
