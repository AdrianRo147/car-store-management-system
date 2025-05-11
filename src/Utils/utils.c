#include "utils.h"

#include "../Vehicle/vehicle.h"
#include "../Customer/customer.h"
#include "../Employee/employee.h"
#include "../File/file.h"

#include <stdio.h>
#include <string.h>

bool StringCopy(char* pSrc, char* pDst, size_t DstSize)
{
  const size_t SrcSize = strlen(pSrc);

  if (DstSize < SrcSize || pSrc == NULL || pDst == NULL)
    return false;

  for (size_t i = 0; i < DstSize - 1; i++)
  {
    if (i > SrcSize)
      break;

    *(pDst + i) = *(pSrc + i);
  }

  *(pDst + DstSize - 1) = 0;

  return true;
}

void ClearStdin()
{
  while (fgetc(stdin) != '\n') {}
}

void ExitApp()
{
  SaveDatabase(pVehiclesList, pCustomersList, pEmployeesList);
  FreeVehicles();
  FreeCustomers();
  FreeEmployees();
  CloseFile();

  exit(0);
}
