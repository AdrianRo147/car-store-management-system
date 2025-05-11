#ifndef FILE_H
#define FILE_H

#include "../LinkedList/linked_list.h"

#include <stdio.h>
#include <stdbool.h>

extern char szFilename[60];
extern FILE* pFile;

enum eSections {
  NONE,
  VEHICLE,
  CUSTOMER,
  EMPLOYEE
};

extern bool OpenReadFile();
extern bool OpenWriteFile();
extern void CloseFile();
extern bool ReadDatabase();
extern void SaveDatabase(struct LinkedList* pVehiclesList, struct LinkedList* pCustomersList, struct LinkedList* pEmployeesList);

#endif
