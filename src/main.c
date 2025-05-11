#include "Vehicle/vehicle.h"
#include "Customer/customer.h"
#include "Employee/employee.h"
#include "File/file.h"
#include "Utils/utils.h"
#include "Input/input.h"

#include <stdio.h>

#ifndef _WIN32
#include <signal.h>

void SignalHandler()
{
  ExitApp();
}

#endif

int main(int argc, char** argv)
{
  InitVehicle(NULL);
  InitCustomers(NULL);
  InitEmployees(NULL);

#ifndef _WIN32
  signal(SIGINT, &SignalHandler);
  signal(SIGHUP, &SignalHandler);
  signal(SIGTERM, &SignalHandler);
#endif

  if (argc > 1)
  {
    const bool bResult = StringCopy(*(argv + 1), szFilename, sizeof(szFilename));

    if (!bResult)
    {
      printf("Database file name cannot be longer that 59 characters");
      ExitApp();
    }
  }
  else
  {
    StringCopy("database.db", szFilename, sizeof(szFilename));
  }

  if (OpenReadFile() && !ReadDatabase())
      printf("Error occured reading database, database might be corrupted!\n\n");

  printf("Car store management system\n\n");

  while (1)
  {
    CategoryInput();
  }
}
