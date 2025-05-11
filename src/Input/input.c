#include "input.h"
#include "../Utils/utils.h"
#include "../Date/date.h"
#include "../Customer/customer.h"
#include "../Employee/employee.h"
#include "../Vehicle/vehicle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CategoryInput()
{
  char cSelection = 0;
  int iSelectionNum = 0;

  printf("Select category:\n");
  printf("1. Vehicles management\n");
  printf("2. Customers management\n");
  printf("3. Employee management\n");
  printf("4. Exit\n");
  printf("Selection (enter 'c' to cancel): ");

Input:
  cSelection = (char)fgetc(stdin);
  ClearStdin();

  if (cSelection == 'c')
  {
    printf("\n");
    return;
  }

  if (cSelection >= '1' && cSelection <= '9')
  {
    iSelectionNum = atoi(&cSelection);
  }
  else
  {
    printf("Invalid input, please, try again: ");
    goto Input;
  }

  switch (iSelectionNum)
  {
    case 1:
      printf("\n");
      VehicleSelectionInput();
      break;
    case 2:
      printf("\n");
      CustomerSelectionInput();
      break;
    case 3:
      printf("\n");
      EmployeeSelectionInput();
      break;
    case 4:
      ExitApp();
      break;
    default:
      printf("Entered category does not exist, please, try again: ");
      goto Input;
  }
}

void VehicleSelectionInput()
{
  char cSelection = 0;
  int iSelectionNum = 0;

  printf("1. List vehicles\n");
  printf("2. Print vehicle details\n");
  printf("3. Add vehicle\n");
  printf("4. Remove vehicle\n");
  printf("5. Update vehicle\n");
  printf("6. Sell specific vehicle\n");
  printf("7. Revert vehicle sale\n");
  printf("8. Back\n");
  printf("Selection (enter 'c' to cancel): ");

Input:
  cSelection = (char)fgetc(stdin);
  ClearStdin();

  if (cSelection == 'c')
  {
    printf("\n");
    return;
  }

  if (cSelection >= '1' && cSelection <= '9')
    iSelectionNum = atoi(&cSelection);

  else
  {
    printf("Invalid input, please, try again: ");
    goto Input;
  }

  switch (iSelectionNum)
  {
    case 1:
      printf("\n");
      PrintAllVehicles();
      break;
    case 2:
      printf("\n");
      PrintVehicleInput();
      break;
    case 3:
      printf("\n");
      AddVehicleInput();
      break;
    case 4:
      printf("\n");
      RemoveVehicleInput();
      break;
    case 5:
      printf("\n");
      UpdateVehicleInput();
      break;
    case 6:
      printf("\n");
      SellVehicleInput();
      break;
    case 7:
      printf("\n");
      RevertVehicleSaleInput();
      break;
    case 8:
      printf("\n");
      break;
    default:
      printf("Entered action does not exist, please, try again: ");
      goto Input;
  }
}

void CustomerSelectionInput()
{
  char cSelection = 0;
  int iSelectionNum = 0;

  printf("1. List customers\n");
  printf("2. Print customer details\n");
  printf("3. Add customer\n");
  printf("4. Remove customer\n");
  printf("5. Update customer\n");
  printf("6. Back\n");
  printf("Selection (enter 'c' to cancel): ");

Input:
  cSelection = (char)fgetc(stdin);
  ClearStdin();

  if (cSelection == 'c')
  {
    printf("\n");
    return;
  }

  if (cSelection >= '1' && cSelection <= '9')
    iSelectionNum = atoi(&cSelection);

  else
  {
    printf("Invalid input, please, try again: ");
    goto Input;
  }

  switch (iSelectionNum)
  {
    case 1:
      printf("\n");
      PrintAllCustomers();
      break;
    case 2:
      printf("\n");
      PrintCustomerInput();
      break;
    case 3:
      printf("\n");
      AddCustomerInput();
      break;
    case 4:
      printf("\n");
      RemoveCustomerInput();
      break;
    case 5:
      printf("\n");
      UpdateCustomerInput();
      break;
    case 6:
      printf("\n");
      break;
    default:
      printf("Entered action does not exist, please, try again\n");
      goto Input;
  }
}

void EmployeeSelectionInput()
{
  char cSelection = 0;
  int iSelectionNum = 0;

  printf("1. List employees\n");
  printf("2. Print employee details\n");
  printf("3. Add employee\n");
  printf("4. Remove employee\n");
  printf("5. Update employee\n");
  printf("6. Back\n");
  printf("Selection (enter 'c' to cancel): ");

Input:
  cSelection = (char)fgetc(stdin);
  ClearStdin();

  if (cSelection == 'c')
  {
    printf("\n");
    return;
  }

  if (cSelection >= '1' && cSelection <= '9')
    iSelectionNum = atoi(&cSelection);

  else
  {
    printf("Invalid input, please, try again: ");
    goto Input;
  }

  switch (iSelectionNum)
  {
    case 1:
      printf("\n");
      PrintAllEmployees();
      break;
    case 2:
      printf("\n");
      PrintEmployeeInput();
      break;
    case 3:
      printf("\n");
      AddEmployeeInput();
      break;
    case 4:
      printf("\n");
      RemoveEmployeeInput();
      break;
    case 5:
      printf("\n");
      UpdateEmployeeInput();
      break;
    case 6:
      printf("\n");
      break;
    default:
      printf("Entered action does not exist, please, try again\n");
      goto Input;
  }
}

void AddVehicleInput()
{
  char szManufacturer[101] = { 0 };
  char szModel[101] = { 0 };
  char szVin[18] = { 0 };

  unsigned int iKilometersDriven = 0;
  char szKilometersDriven[8] = { 0 };

  char szManufactionDate[21] = { 0 };
  unsigned char cDay = 0, cMonth = 0;
  unsigned short sYear = 0;
  struct Date ManufactionDate;

  printf("Manufacturer (max. 100 characters, enter 'c' to cancel): ");
  scanf("%100s", szManufacturer);
  ClearStdin();

  if (!strcmp(szManufacturer, "c"))
  {
    printf("\n");
    return;
  }

  printf("Model (max. 100 characters, enter 'c' to cancel): ");
  scanf("%100s", szModel);
  ClearStdin();

  if (!strcmp(szManufacturer, "c"))
  {
    printf("\n");
    return;
  }

  printf("VIN (max. 17 characters, enter 'c' to cancel): ");

VinInput:
  scanf("%17s", szVin);
  ClearStdin();

  if (!strcmp(szVin, "c"))
  {
    printf("\n");
    return;
  }

  if (IsVinDuplicate(szVin))
  {
    memset(szVin, 0, sizeof(szVin));
    printf("Entered VIN code is already assigned to another vehicle, please, try again: ");
    goto VinInput;
  }

  printf("Manufaction date (Format: DD/MM/YYYY, enter 'c' to cancel): ");

ManufactionDateInput:
  scanf("%20s", szManufactionDate);
  ClearStdin();

  if (!strcmp(szManufactionDate, "c"))
  {
    printf("\n");
    return;
  }

  const int iManufactionDateResult = sscanf(szManufactionDate, "%2hhu/%2hhu/%4hu", &cDay, &cMonth, &sYear);

  if (iManufactionDateResult != 3)
  {
    memset(szManufactionDate, 0, sizeof(szManufactionDate));
    printf("Invalid input, please, try again: ");
    goto ManufactionDateInput;
  }

  InitDate(&ManufactionDate, cDay, cMonth, sYear);

  printf("Kilometers driven (enter 'c' to cancel): ");

KilometersDrivenInput:
  memset(szKilometersDriven, 0, sizeof(szKilometersDriven));
  scanf("%7s", szKilometersDriven);
  ClearStdin();

  if (!strcmp(szKilometersDriven, "c"))
  {
    printf("\n");
    return;
  }

  if (!strcmp(szKilometersDriven, "-"))
  {
    printf("Invalid input, please, try again: ");
    goto KilometersDrivenInput;
  }

  for (size_t i = 0; i < sizeof(szKilometersDriven); i++)
  {
    if (!(*(szKilometersDriven + i) >= '0' && *(szKilometersDriven + i) <= '9') && (*(szKilometersDriven + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto KilometersDrivenInput;
    }
  }

  iKilometersDriven = atoi(szKilometersDriven);
  AddVehicle(szManufacturer, szModel, szVin, ManufactionDate, iKilometersDriven);
  printf("\nVehicle was added\n\n");
}

void RemoveVehicleInput()
{
  unsigned short sId = 0;
  char szId[6] = { 0 };

  struct Vehicle* pVehicle = NULL;
  printf("Enter ID of vehicle you wish to remove (enter 'c' to cancel): ");

IdInput:
  memset(szId, 0, sizeof(szId));
  scanf("%5s", szId);
  ClearStdin();

  if (!strcmp(szId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szId); i++)
  {
    if (!(*(szId + i) >= '0' && *(szId + i) <= '9') && (*(szId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto IdInput;
    }
  }

  sId = (unsigned short)atoi(szId);

  if (!GetVehicle(sId, &pVehicle))
  {
    printf("Vehicle with entered ID does not exist, please, try again: ");
    goto IdInput;
  }

  RemoveVehicle(pVehicle);
}

void UpdateVehicleInput()
{
  int sId = 0;
  char szId[6] = { 0 };

  struct Vehicle* pVehicle = NULL;

  printf("Enter ID of vehicle you wish to update: ");

IdInput:
  memset(szId, 0, sizeof(szId));
  scanf("%5s", szId);
  ClearStdin();

  if (!strcmp(szId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szId); i++)
  {
    if (!(*(szId + i) >= '0' && *(szId + i) <= '9') && (*(szId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto IdInput;
    }
  }

  sId = atoi(szId);

  if (!GetVehicle(sId, &pVehicle))
  {
    printf("Vehicle with entered ID does not exist, please, try again: ");
    goto IdInput;
  }

  char szManufacturer[101] = { 0 };
  char szModel[101] = { 0 };
  char szVin[18] = { 0 };

  unsigned int iKilometersDriven = 0;
  char szKilometersDriven[8] = { 0 };

  char szManufactionDate[21] = { 0 };
  unsigned char cDay = 0, cMonth = 0;
  unsigned short sYear = 0;
  struct Date ManufactionDate = { 0, 0, 0 };

  printf("Manufacturer (Enter '.' for no changes, 'c' to cancel, max. 100 characters): ");
  scanf("%100s", szManufacturer);
  ClearStdin();

  if (!strcmp(szManufacturer, "c"))
  {
    printf("\n");
    return;
  }

  printf("Model (Enter '.' for no changes, 'c' to cancel, max. 100 characters): ");
  scanf("%100s", szModel);
  ClearStdin();

  if (!strcmp(szModel, "c"))
  {
    printf("\n");
    return;
  }

  printf("VIN (Enter '.' for no changes, 'c' to cancel, max. 17 characters): ");

VinInput:
  memset(szVin, 0, sizeof(szVin));
  scanf("%17s", szVin);
  ClearStdin();

  if (!strcmp(szVin, "c"))
  {
    printf("\n");
    return;
  }

  if (IsVinDuplicate(szVin))
  {
    printf("Entered VIN code is already assigned to another vehicle, please, try again: ");
    goto VinInput;
  }

  printf("Manufaction date (Enter '.' for no changes, 'c' to cancel, Format: DD/MM/YYYY): ");

ManufactionDateInput:
  memset(szManufactionDate, 0, sizeof(szManufactionDate));
  scanf("%20s", szManufactionDate);
  ClearStdin();

  if (!strcmp(szManufactionDate, "c"))
  {
    printf("\n");
    return;
  }

  const int iManufactionDateResult = sscanf(szManufactionDate, "%2hhu/%2hhu/%4hu", &cDay, &cMonth, &sYear);

  if (iManufactionDateResult != 3 && strcmp(szManufactionDate, "."))
  {
    printf("Invalid input, please, try again: ");
    goto ManufactionDateInput;
  }

  InitDate(&ManufactionDate, cDay, cMonth, sYear);

  printf("Kilometers driven (Enter '.' for no changes, 'c' to cancel): ");

KilometersDrivenInput:
  memset(szKilometersDriven, 0, sizeof(szKilometersDriven));
  scanf("%7s", szKilometersDriven);
  ClearStdin();

  if (!strcmp(szKilometersDriven, "c"))
  {
    printf("\n");
    return;
  }

  if (!strcmp(szKilometersDriven, "-"))
  {
    printf("Invalid input, please, try again: ");
    goto KilometersDrivenInput;
  }

  if (!strcmp(szKilometersDriven, "."))
  {
    iKilometersDriven = (unsigned int)-1;
    goto SkipKilometers;
  }

  for (size_t i = 0; i < sizeof(szKilometersDriven); i++)
  {
    if (!(*(szKilometersDriven + i) >= '0' && *(szKilometersDriven + i) <= '9') && (*(szKilometersDriven + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto KilometersDrivenInput;
    }
  }

  iKilometersDriven = atoi(szKilometersDriven);

SkipKilometers:
  UpdateVehicle(pVehicle, szManufacturer, szModel, szVin, ManufactionDate, iKilometersDriven);
  printf("\nVehicle was updated\n\n");
}

void SellVehicleInput()
{
  unsigned short sVehicleId = 0;
  char szVehicleId[6] = { 0 };

  unsigned short sCustomerId = 0;
  char szCustomerId[6] = { 0 };

  unsigned short sEmployeeId = 0;
  char szEmployeeId[6] = { 0 };

  struct Vehicle* pVehicle = NULL;
  struct Customer* pCustomer = NULL;
  struct Employee* pEmployee = NULL;

  printf("Enter vehicle ID (enter 'c' to cancel): ");
VehicleIdInput:
  memset(szVehicleId, 0, sizeof(szVehicleId));
  scanf("%5s", szVehicleId);
  ClearStdin();

  if (!strcmp(szVehicleId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szVehicleId); i++)
  {
    if (!(*(szVehicleId + i) >= '0' && *(szVehicleId + i) <= '9') && (*(szVehicleId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto VehicleIdInput;
    }
  }

  sVehicleId = (unsigned short)atoi(szVehicleId);

  if (!GetVehicle(sVehicleId, &pVehicle))
  {
    printf("Vehicle with entered ID does not exist, please, try again: ");
    goto VehicleIdInput;
  }

  printf("Enter customer ID who bought the vehicle: ");
CustomerIdInput:
  memset(szCustomerId, 0, sizeof(szCustomerId));
  scanf("%5s", szCustomerId);
  ClearStdin();

  if (!strcmp(szCustomerId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szCustomerId); i++)
  {
    if (!(*(szCustomerId + i) >= '0' && *(szCustomerId + i) <= '9') && (*(szCustomerId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto CustomerIdInput;
    }
  }

  sCustomerId = (unsigned short)atoi(szCustomerId);

  if (!GetCustomer(sCustomerId, &pCustomer))
  {
    printf("Customer with entered ID does not exist, please, try again: ");
    goto CustomerIdInput;
  }

  printf("Enter employee ID who sold the vehicle: ");
EmployeeIdInput:
  memset(szEmployeeId, 0, sizeof(szEmployeeId));
  scanf("%5s", szEmployeeId);
  ClearStdin();

  if (!strcmp(szEmployeeId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szEmployeeId); i++)
  {
    if (!(*(szEmployeeId + i) >= '0' && *(szEmployeeId + i) <= '9') && (*(szEmployeeId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto EmployeeIdInput;
    }
  }

  sEmployeeId = (unsigned short)atoi(szEmployeeId);

  if (!GetEmployee(sEmployeeId, &pEmployee))
  {
    printf("Employee with entered ID does not exist, please, try again: ");
    goto CustomerIdInput;
  }

  SellVehicle(pVehicle, pCustomer, pEmployee);

  printf("\nVehicle was sold\n\n");
}

void RevertVehicleSaleInput()
{
  unsigned short sId = 0;
  char szId[6] = { 0 };
  struct Vehicle* pVehicle = NULL;

  printf("Enter vehicle ID (enter 'c' to cancel): ");
IdInput:
  memset(szId, 0, sizeof(szId));
  scanf("%5s", szId);
  ClearStdin();

  if (!strcmp(szId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szId); i++)
  {
    if (!(*(szId + i) >= '0' && *(szId + i) <= '9') && (*(szId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto IdInput;
    }
  }

  sId = (unsigned short)atoi(szId);

  if (!GetVehicle(sId, &pVehicle))
  {
    printf("Vehicle with entered ID does not exist, please, try again: ");
    goto IdInput;
  }

  if (!RevertVehicleSale(pVehicle))
  {
    printf("Failed to revert vehicle sale, database might be corrupted!\n\n");
    return;
  }

  printf("\nSale of vehicle was successfully reverted\n\n");
}

void PrintVehicleInput()
{
  unsigned short sId = 0;
  char szId[6] = { 0 };

  struct Vehicle* pVehicle = NULL;

  printf("Enter vehicle ID (enter 'c' to cancel): ");
Input:
  memset(szId, 0, sizeof(szId));
  scanf("%5s", szId);
  ClearStdin();

  if (!strcmp(szId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szId); i++)
  {
    if (!(*(szId + i) >= '0' && *(szId + i) <= '9') && (*(szId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto Input;
    }
  }

  sId = (unsigned short)atoi(szId);

  if (!GetVehicle(sId, &pVehicle))
  {
    printf("Vehicle with entered ID does not exist, please, try again: ");
    goto Input;
  }

  PrintVehicle(pVehicle);
}

void AddCustomerInput()
{
  char szFirstName[101] = { 0 };
  char szSurname[101] = { 0 };
  char cDateOfBirth[11] = { 0 };
  unsigned char cDay = 0, cMonth = 0;
  unsigned short sYear = 0;
  struct Date DateOfBirth;

  printf("First name (max. 100 characters, enter 'c' to cancel): ");
  scanf("%100s", szFirstName);
  ClearStdin();

  if (!strcmp(szFirstName, "c"))
  {
    printf("\n");
    return;
  }

  printf("Surname (max. 100 characters, enter 'c' to cancel): ");
  scanf("%100s", szSurname);
  ClearStdin();

  if (!strcmp(szSurname, "c"))
  {
    printf("\n");
    return;
  }

  printf("Date of Birth (Format: DD/MM/YYYY, enter 'c' to cancel): ");

DateOfBirthInput:
  scanf("%10s", cDateOfBirth);
  ClearStdin();

  if (!strcmp(cDateOfBirth, "c"))
  {
    printf("\n");
    return;
  }

  const int iDateOfBirthResult = sscanf(cDateOfBirth, "%2hhu/%2hhu/%4hu", &cDay, &cMonth, &sYear);

  if (iDateOfBirthResult != 3)
  {
    memset(cDateOfBirth, 0, sizeof(cDateOfBirth));
    printf("Invalid input, please, try again: ");
    goto DateOfBirthInput;
  }

  InitDate(&DateOfBirth, cDay, cMonth, sYear);
  AddCustomer(szFirstName, szSurname, DateOfBirth);
  printf("\nCustomer was added\n\n");
}

void RemoveCustomerInput()
{
  unsigned short sId = 0;
  char szId[6] = { 0 };

  struct Customer* pCustomer = NULL;
  printf("Enter ID of customer you wish to remove: ");

IdInput:
  memset(szId, 0, sizeof(szId));
  scanf("%5s", szId);
  ClearStdin();

  if (!strcmp(szId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szId); i++)
  {
    if (!(*(szId + i) >= '0' && *(szId + i) <= '9') && (*(szId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto IdInput;
    }
  }

  sId = (unsigned short)atoi(szId);

  if (!GetCustomer(sId, &pCustomer))
  {
    printf("Customer with entered ID does not exist, please, try again: ");
    goto IdInput;
  }

  printf("\n");
  RemoveCustomer(pCustomer);
}

void UpdateCustomerInput()
{
  unsigned short sId = 0;
  char szId[6] = { 0 };

  struct Customer* pCustomer = NULL;

  printf("Enter ID of customer you wish to update:" );

IdInput:
  memset(szId, 0, sizeof(szId));
  scanf("%5s", szId);
  ClearStdin();

  if (!strcmp(szId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szId); i++)
  {
    if (!(*(szId + i) >= '0' && *(szId + i) <= '9') && (*(szId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto IdInput;
    }
  }

  sId = atoi(szId);

  if (!GetCustomer(sId, &pCustomer))
  {
    printf("Customer with entered ID does not exist, please, try again: ");
    goto IdInput;
  }

  char szFirstName[101] = { 0 };
  char szSurname[101] = { 0 };
  char szDateOfBirth[21] = { 0 };

  unsigned char cDateOfBirthDay = 0, cDateOfBirthMonth = 0;
  unsigned short sDateOfBirthYear = 0;
  struct Date DateOfBirth = { 0, 0, 0 };

  printf("First name (enter '.' for no changes, 'c' to cancel, max. 100 characters): ");
  scanf("%100s", szFirstName);
  ClearStdin();

  if (!strcmp(szFirstName, "c"))
  {
    printf("\n");
    return;
  }

  printf("Surname (Enter '.' for no changes, 'c' to cancel, max. 100 characters): ");
  scanf("%100s", szSurname);
  ClearStdin();

  if (!strcmp(szSurname, "c"))
  {
    printf("\n");
    return;
  }

  printf("Date of birth (Enter '.' for no changes, 'c' to cancel, Format: DD/MM/YYYY): ");

DateOfBirthInput:
  memset(szDateOfBirth, 0, sizeof(szDateOfBirth));
  scanf("%20s", szDateOfBirth);
  ClearStdin();

  if (!strcmp(szDateOfBirth, "c"))
  {
    printf("\n");
    return;
  }

  const int iDateOfBirthResult = sscanf(szDateOfBirth, "%2hhu/%2hhu/%4hu", &cDateOfBirthDay, &cDateOfBirthMonth, &sDateOfBirthYear);

  if (iDateOfBirthResult != 3 && strcmp(szDateOfBirth, "."))
  {
    printf("Invalid input, please, try again: ");
    goto DateOfBirthInput;
  }

  InitDate(&DateOfBirth, cDateOfBirthDay, cDateOfBirthMonth, sDateOfBirthYear);

  UpdateCustomer(pCustomer, szFirstName, szSurname, DateOfBirth);
  printf("\nCustomer was updated\n\n");
}

void PrintCustomerInput()
{
  unsigned short sId = 0;
  char szId[6] = { 0 };

  struct Customer* pCustomer = NULL;

  printf("Enter customer ID (enter 'c' to cancel): ");
  Input:
  memset(szId, 0, sizeof(szId));
  scanf("%5s", szId);
  ClearStdin();

  if (!strcmp(szId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szId); i++)
  {
    if (!(*(szId + i) >= '0' && *(szId + i) <= '9') && (*(szId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto Input;
    }
  }

  sId = (unsigned short)atoi(szId);

  if (!GetCustomer(sId, &pCustomer))
  {
    printf("Customer with entered ID does not exist, please, try again: ");
    goto Input;
  }

  printf("\n");
  PrintCustomer(pCustomer);
}

void AddEmployeeInput()
{
  char szFirstName[101] = { 0 };
  char szSurname [101] = { 0 };
  char szDateOfBirth[11] = { 0 };
  char szEmployedUntil[11] = { 0 };

  unsigned char cDateOfBirthDay = 0, cDateOfBirthMonth = 0;
  unsigned short sDateOfBirthYear = 0;
  struct Date DateOfBirth;

  unsigned char cEmployedUntilDay = 0, cEmployedUntilMonth = 0;
  unsigned short sEmployedUntilYear = 0;
  struct Date dateEmployedUntil;

  printf("First name (max. 100 characters, enter 'c' to cancel): ");
  scanf("%100s", szFirstName);
  ClearStdin();

  if (!strcmp(szFirstName, "c"))
  {
    printf("\n");
    return;
  }

  printf("Surname (max. 100 characters, enter 'c' to cancel): ");
  scanf("%100s", szSurname);
  ClearStdin();

  if (!strcmp(szSurname, "c"))
  {
    printf("\n");
    return;
  }

  printf("Date of Birth (Format: DD/MM/YYYY, enter 'c' to cancel): ");

DateOfBirthInput:
  scanf("%10s", szDateOfBirth);
  ClearStdin();

  if (!strcmp(szDateOfBirth, "c"))
  {
    printf("\n");
    return;
  }

  const int iDateOfBirthResult = sscanf(szDateOfBirth, "%2hhu/%2hhu/%4hu", &cDateOfBirthDay, &cDateOfBirthMonth, &sDateOfBirthYear);

  if (iDateOfBirthResult != 3)
  {
    memset(szDateOfBirth, 0, sizeof(szDateOfBirth));
    printf("Invalid input, please, try again: ");
    goto DateOfBirthInput;
  }

  InitDate(&DateOfBirth, cDateOfBirthDay, cDateOfBirthMonth, sDateOfBirthYear);

  printf("Employeed until (Date until employee is employed, enter 'c' to cancel, enter '.' for default, Format: DD/MM/YYYY, Default: 1 year after current date): ");

EmployeedUntilInput:
  scanf("%10s", szEmployedUntil);
  ClearStdin();

  if (!strcmp(szEmployedUntil, "c"))
  {
    printf("\n");
    return;
  }

  const int iEmployedUntilResult = sscanf(szEmployedUntil, "%2hhu/%2hhu/%4hu", &cEmployedUntilDay, &cEmployedUntilMonth, &sEmployedUntilYear);

  if (iEmployedUntilResult != 3 && strcmp(szEmployedUntil, "."))
  {
    memset(szEmployedUntil, 0, sizeof(szEmployedUntil));
    printf("Invalid input, please, try again: ");
    goto EmployeedUntilInput;
  }

  struct Date CurrentDate;
  SetCurrentDate(&CurrentDate);

  if (!strcmp(szEmployedUntil, "."))
  {
    cEmployedUntilDay = CurrentDate.cDay;
    cEmployedUntilMonth = CurrentDate.cMonth;
    sEmployedUntilYear = CurrentDate.sYear + 1;
  }

  InitDate(&dateEmployedUntil, cEmployedUntilDay, cEmployedUntilMonth, sEmployedUntilYear);

  AddEmployee(szFirstName, szSurname, DateOfBirth, dateEmployedUntil);

  printf("\nEmployee was added\n\n");
}

void RemoveEmployeeInput()
{
  unsigned short sId = 0;
  char szId[6] = { 0 };

  struct Employee* pEmployee = NULL;
  printf("Enter ID of employee you wish to remove: ");

IdInput:
  memset(szId, 0, sizeof(szId));
  scanf("%5s", szId);
  ClearStdin();

  if (!strcmp(szId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szId); i++)
  {
    if (!(*(szId + i) >= '0' && *(szId + i) <= '9') && (*(szId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto IdInput;
    }
  }

  sId = (unsigned short)atoi(szId);

  if (!GetEmployee(sId, &pEmployee))
  {
    printf("Employee with entered ID does not exist, please, try again: ");
    goto IdInput;
  }

  printf("\n");
  RemoveEmployee(pEmployee);
}

void UpdateEmployeeInput()
{
  unsigned short sId = 0;
  char szId[6] = { 0 };

  struct Employee* pEmployee = NULL;
  printf("Enter ID of employee you wish to remove: ");

IdInput:
  memset(szId, 0, sizeof(szId));
  scanf("%5s", szId);
  ClearStdin();

  if (!strcmp(szId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szId); i++)
  {
    if (!(*(szId + i) >= '0' && *(szId + i) <= '9') && (*(szId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto IdInput;
    }
  }

  sId = atoi(szId);

  if (!GetEmployee(sId, &pEmployee))
  {
    printf("Employee with entered ID does not exist, please, try again: ");
    goto IdInput;
  }

  char szFirstName[101] = { 0 };
  char szSurname[101] = { 0 };
  char szDateOfBirth[21] = { 0 };
  char szEmployedUntil[21] = { 0 };

  unsigned char cDateOfBirthDay = 0, cDateOfBirthMonth = 0;
  unsigned short sDateOfBirthYear = 0;
  struct Date DateOfBirth = { 0, 0, 0 };

  unsigned char cEmployedUntilDay = 0, cEmployedUntilMonth = 0;
  unsigned short sEmployedUntilYear = 0;
  struct Date dateEmployedUntil = { 0, 0, 0 };

  printf("First name (enter '.' for no changes, 'c' to cancel, max. 100 characters): ");
  scanf("%100s", szFirstName);
  ClearStdin();

  if (!strcmp(szFirstName, "c"))
  {
    printf("\n");
    return;
  }

  printf("Surname (enter '.' for no changes, 'c' to cancel, max. 100 characters): ");
  scanf("%100s", szSurname);
  ClearStdin();

  if (!strcmp(szSurname, "c"))
  {
    printf("\n");
    return;
  }

  printf("Date of birth (enter '.' for no changes, 'c' to cancel, Format: DD/MM/YYYY): ");

DateOfBirthInput:
  memset(szDateOfBirth, 0, sizeof(szDateOfBirth));
  scanf("%20s", szDateOfBirth);
  ClearStdin();

  if (!strcmp(szDateOfBirth, "c"))
  {
    printf("\n");
    return;
  }

  const int iDateOfBirthResult = sscanf(szDateOfBirth, "%2hhu/%2hhu/%4hu", &cDateOfBirthDay, &cDateOfBirthMonth, &sDateOfBirthYear);

  if (iDateOfBirthResult != 3 && strcmp(szDateOfBirth, "."))
  {
    printf("Invalid input, please, try again: ");
    goto DateOfBirthInput;
  }

  InitDate(&DateOfBirth, cDateOfBirthDay, cDateOfBirthMonth, sDateOfBirthYear);

  printf("Employed until (enter '.' for no changes, 'c' to cancel, Format: DD/MM/YYYY): ");

EmployedUntilInput:
  memset(szEmployedUntil, 0, sizeof(szEmployedUntil));
  scanf("%20s", szEmployedUntil);
  ClearStdin();

  if (!strcmp(szEmployedUntil, "c"))
  {
    printf("\n");
    return;
  }

  const int iEmployedUntilResult = sscanf(szEmployedUntil, "%2hhu/%2hhu/%4hu", &cEmployedUntilDay, &cEmployedUntilMonth, &sEmployedUntilYear);

  if (iEmployedUntilResult != 3 && strcmp(szEmployedUntil, "."))
  {
    printf("Invalid input, please, try again: ");
    goto EmployedUntilInput;
  }

  InitDate(&dateEmployedUntil, cEmployedUntilDay, cEmployedUntilMonth, sEmployedUntilYear);

  UpdateEmployee(pEmployee, szFirstName, szSurname, DateOfBirth, dateEmployedUntil);
  printf("\nEmployee was updated\n\n");
}

void PrintEmployeeInput()
{
  unsigned short sId = 0;
  char szId[6] = { 0 };

  struct Employee* pEmployee = NULL;

  printf("Enter employee ID (enter 'c' to cancel): ");
  IdInput:
  memset(szId, 0, sizeof(szId));
  scanf("%5s", szId);
  ClearStdin();

  if (!strcmp(szId, "c"))
  {
    printf("\n");
    return;
  }

  for (size_t i = 0; i < sizeof(szId); i++)
  {
    if (!(*(szId + i) >= '0' && *(szId + i) <= '9') && (*(szId + i) != 0))
    {
      printf("Invalid input, please, try again: ");
      goto IdInput;
    }
  }

  sId = (unsigned short)atoi(szId);

  if (!GetEmployee(sId, &pEmployee))
  {
    printf("Employee with entered ID does not exist, please, try again: ");
    goto IdInput;
  }

  printf("\n");
  PrintEmployee(pEmployee);
}
