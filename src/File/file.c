#include "file.h"

#include "../Vehicle/vehicle.h"
#include "../Customer/customer.h"
#include "../Employee/employee.h"
#include "../Utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char szFilename[60] = { 0 };
FILE* pFile = NULL;

bool OpenReadFile()
{
  pFile = fopen(szFilename, "r");

  if (pFile == NULL)
    return false;

  return true;
}

bool OpenWriteFile()
{
  pFile = fopen(szFilename, "w");

  if (pFile == NULL)
    return false;

  return true;
}

void CloseFile()
{
  if (pFile != NULL)
  {
    fclose(pFile);
    pFile = NULL;
  }
}

bool ReadDatabase()
{
  char line[128] = { 0 };
  enum eSections eSection = NONE;
  bool bReturn = false;

  fgets(line, sizeof(line), pFile);

  if (strcmp(line, "\\beginFile\n"))
  {
    bReturn = false;
    goto End;
  }

  while (fgets(line, sizeof(line), pFile))
  {
    if (*line == '\n')
    {
      eSection = NONE;
      continue;
    }

    if (*(line + strlen(line) - 1) == '\n')
      *(line + strlen(line) - 1) = 0;

    if (!strcmp(line, "\\beginVehicle"))
    {
      eSection = VEHICLE;
      continue;
    }

    if (!strcmp(line, "\\endVehicle"))
    {
      eSection = NONE;
      continue;
    }

    if (!strcmp(line, "\\beginCustomer"))
    {
      eSection = CUSTOMER;
      continue;
    }

    if (!strcmp(line, "\\endCustomer"))
    {
      eSection = NONE;
      continue;
    }

    if (!strcmp(line, "\\beginEmployee"))
    {
      eSection = EMPLOYEE;
      continue;
    }

    if (!strcmp(line, "\\endEmployee"))
    {
      eSection = NONE;
      continue;
    }

    if (!strcmp(line, "\\endFile"))
    {
      bReturn = true;
      goto End;
    }

    if (eSection == VEHICLE)
    {
      /* Parse ID, don't need to use fgets,
       * new line was already readed as its in loop condition
       */
      for (size_t i = 0; i < strlen(line); i++)
      {
        if (!(*(line + i) >= '0' && *(line + i) <= '9') && (*(line + i) <= 0))
        {
          bReturn = false;
          goto End;
        }
      }

      unsigned short sVehicleId = (unsigned short)atoi(line);

      // Parse manufacturer
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      char szManufacturer[101] = { 0 };
      StringCopy(line, szManufacturer, sizeof(szManufacturer));

      // Parse model
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      char szModel[101] = { 0 };
      StringCopy(line, szModel, sizeof(szModel));

      // Parse VIN
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      char szVin[18] = { 0 };
      StringCopy(line, szVin, sizeof(szVin));

      // Parse manufaction date
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      unsigned char cManufactionDay = 0, cManufactionMonth = 0;
      unsigned short sManufactionYear = 0;

      int iManufactionDateResult = sscanf(line, "%2hhu. %2hhu. %4hu", &cManufactionDay, &cManufactionMonth, &sManufactionYear);

      if (iManufactionDateResult != 3)
      {
        bReturn = false;
        goto End;
      }

      struct Date ManufactionDate = { 0 };
      InitDate(&ManufactionDate, cManufactionDay, cManufactionMonth, sManufactionYear);

      // Parse kilometers driven
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      for (size_t i = 0; i < strlen(line); i++)
      {
        if (!(*(line + i) >= '0' && *(line + i) <= '9') && (*(line + i) <= 0))
        {
          bReturn = false;
          goto End;
        }
      }

      unsigned int iKilometersDriven = (unsigned int)atoi(line);

      // Parse created at date
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      unsigned char cCreatedAtDay = 0, cCreatedAtMonth = 0;
      unsigned short sCreatedAtYear = 0;

      int iCreatedAtResult = sscanf(line, "%2hhu. %2hhu. %4hu", &cCreatedAtDay, &cCreatedAtMonth, &sCreatedAtYear);

      if (iCreatedAtResult != 3)
      {
        bReturn = false;
        goto End;
      }

      struct Date dateCreatedAt = { 0 };
      InitDate(&dateCreatedAt, cCreatedAtDay, cCreatedAtMonth, sCreatedAtYear);

      // Parse was sold
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      bool bWasSold;

      if (!strcmp(line, "yes"))
        bWasSold = true;
      else if (!strcmp(line, "no"))
        bWasSold = false;
      else
      {
        bReturn = false;
        goto End;
      }

      // Parse employee ID
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      for (size_t i = 0; i < strlen(line); i++)
      {
        if (!(*(line + i) >= '0' && *(line + i) <= '9') && (*(line + i) <= 0))
        {
          bReturn = false;
          goto End;
        }
      }

      unsigned short sEmployeeId = (unsigned short)atoi(line);

      // Parse customer ID
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      for (size_t i = 0; i < strlen(line); i++)
      {
        if (!(*(line + i) >= '0' && *(line + i) <= '9') && (*(line + i) <= 0))
        {
          bReturn = false;
          goto End;
        }
      }

      unsigned short sCustomerId = (unsigned short)atoi(line);

      // Parse sold at date
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      unsigned char cSoldAtDay = 0, cSoldAtMonth = 0;
      unsigned short sSoldAtYear = 0;

      int iSoldAtResult = sscanf(line, "%2hhu. %2hhu. %4hu", &cSoldAtDay, &cSoldAtMonth, &sSoldAtYear);

      if (iSoldAtResult != 3)
      {
        bReturn = false;
        goto End;
      }

      struct Date dateSoldAt = { 0 };
      InitDate(&dateSoldAt, cSoldAtDay, cSoldAtMonth, sSoldAtYear);

      // Check if next is end vehicle section
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      if (strcmp(line, "\\endVehicle"))
      {
        bReturn = false;
        goto End;
      }

      // Add vehicle
      struct Vehicle* pNew = (struct Vehicle*)malloc(sizeof(struct Vehicle));

      pNew->sId = sVehicleId;
      StringCopy(szManufacturer, pNew->szManufacturer, sizeof(pNew->szManufacturer));
      StringCopy(szModel, pNew->szModel, sizeof(pNew->szModel));
      StringCopy(szVin, pNew->szVin, sizeof(pNew->szVin));
      pNew->ManufactionDate = ManufactionDate;
      pNew->iKilometersDriven = iKilometersDriven;
      pNew->dateCreatedAt = dateCreatedAt;
      pNew->bWasSold = bWasSold;
      pNew->sCustomerId = sCustomerId;
      pNew->sEmployeeId = sEmployeeId;
      pNew->dateSoldAt = dateSoldAt;

      const bool bPushResult = InsertToList(pVehiclesList, (void*)pNew);

      if (!bPushResult)
      {
        bReturn = false;
        goto End;
      }

      continue;
    }

    if (eSection == CUSTOMER)
    {
      /* Parse ID, don't need to use fgets,
       * new line was already readed as its in loop condition
       */
      for (size_t i = 0; i < strlen(line); i++)
      {
        if (!(*(line + i) >= '0' && *(line + i) <= '9') && (*(line + i) <= 0))
        {
          bReturn = false;
          goto End;
        }
      }

      unsigned short sCustomerId = (unsigned short)atoi(line);

      // Parse first name
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      char szFirstName[101] = { 0 };
      StringCopy(line, szFirstName, sizeof(szFirstName));

      // Parse surname
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      char szSurname[101] = { 0 };
      StringCopy(line, szSurname, sizeof(szSurname));

      // Parse date of birth
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      unsigned char cDateOfBirthDay = 0, cDateOfBirthMonth = 0;
      unsigned short sDateOfBirthYear = 0;

      int iDateOfBirthResult = sscanf(line, "%2hhu. %2hhu. %4hu", &cDateOfBirthDay, &cDateOfBirthMonth, &sDateOfBirthYear);

      if (iDateOfBirthResult != 3)
      {
        bReturn = false;
        goto End;
      }

      struct Date DateOfBirth = { 0 };
      InitDate(&DateOfBirth, cDateOfBirthDay, cDateOfBirthMonth, sDateOfBirthYear);

      // Parse created at
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      unsigned char cCreatedAtDay = 0, cCreatedAtMonth = 0;
      unsigned short sCreatedAtYear = 0;

      int iCreatedAtResult = sscanf(line, "%2hhu. %2hhu. %4hu", &cCreatedAtDay, &cCreatedAtMonth, &sCreatedAtYear);

      if (iCreatedAtResult != 3)
      {
        bReturn = false;
        goto End;
      }

      struct Date dateCreatedAt = { 0 };
      InitDate(&dateCreatedAt, cCreatedAtDay, cCreatedAtMonth, sCreatedAtYear);

      // Parse bought vehicles
      struct LinkedList* pBoughtVehiclesList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
      InitLinkedList(pBoughtVehiclesList, NULL);
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      if (!strcmp(line, "null"))
      {
        /* If line is null do nothing, linked list of bought vehicles should be empty in this case.
         * Condition is needed because only valid values are "null", number (e. g. 123) or list (e. g. [1,2,3])
         */
      }
      else if (*line >= '0' && *line <= '9')
      {
        for (size_t i = 0; i < strlen(line); i++)
        {
          if (!(*(line + i) >= '0' && *(line + i) <= '9') && (*(line + i) != 0))
          {
            FreeLinkedList(pBoughtVehiclesList);
            bReturn = false;
            goto End;
          }
        }

        unsigned short* pVehicleId = (unsigned short*)malloc(sizeof(unsigned short));
        *pVehicleId = (unsigned short)atoi(line);

        const bool bPushResult = InsertToList(pBoughtVehiclesList, (void*)pVehicleId);

        if (!bPushResult)
        {
          FreeLinkedList(pBoughtVehiclesList);
          bReturn = false;
          goto End;
        }
      }
      else if (*line == '[' && *(line + strlen(line) - 1) == ']')
      {
        unsigned char cNumbersCount = 0;

        for (size_t i = 0; i < strlen(line); i++)
        {
          if (*(line + i) == ',')
            cNumbersCount++;
        }

        if (cNumbersCount >= 1)
          cNumbersCount++;

        if (cNumbersCount == 0)
          goto SkipParsingListCustomer;

        unsigned char cCurrentCharacter = 0, cCurrentNumber = 0;
        char szVehicleId[6] = { 0 };
        unsigned short sVehicleIds[cNumbersCount];

        memset(sVehicleIds, 0, sizeof(sVehicleIds));

        for (size_t i = 1; i < strlen(line); i++)
        {
          char cCharacter = *(line + i);

          if (cCharacter == ',' || cCharacter == ']')
          {
            *(sVehicleIds + cCurrentNumber) = (unsigned short)atoi(szVehicleId);
            memset(szVehicleId, 0, sizeof(szVehicleId));
            cCurrentCharacter = 0;
            cCurrentNumber++;
          }

          else if (cCharacter >= '0' && cCharacter <= '9')
          {
            if (cCurrentCharacter >= sizeof(szVehicleId))
            {
              FreeLinkedList(pBoughtVehiclesList);
              bReturn = false;
              goto End;
            }

            *(szVehicleId + cCurrentCharacter) = cCharacter;
            cCurrentCharacter++;
          }

          else
          {
            FreeLinkedList(pBoughtVehiclesList);
            bReturn = false;
            goto End;
          }
        }

        for (size_t i = 0; i < cNumbersCount; i++)
        {
          unsigned short* pVehicleId = (unsigned short*)malloc(sizeof(unsigned short));
          *pVehicleId = *(sVehicleIds + i);

          const bool bPushResult = InsertToList(pBoughtVehiclesList, (void*)pVehicleId);

          if (!bPushResult)
          {
            FreeLinkedList(pBoughtVehiclesList);
            bReturn = false;
            goto End;
          }
        }
      }
      else
      {
        FreeLinkedList(pBoughtVehiclesList);
        bReturn = false;
        goto End;
      }

SkipParsingListCustomer:
      // Check if next line is \endCustomer
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      if (strcmp(line, "\\endCustomer"))
      {
        FreeLinkedList(pBoughtVehiclesList);
        bReturn = false;
        goto End;
      }

      // Add customer
      struct Customer* pNew = (struct Customer*)malloc(sizeof(struct Customer));

      pNew->sId = sCustomerId;
      StringCopy(szFirstName, pNew->szFirstName, sizeof(pNew->szFirstName));
      StringCopy(szSurname, pNew->szSurname, sizeof(pNew->szSurname));
      pNew->DateOfBirth = DateOfBirth;
      pNew->dateCreatedAt = dateCreatedAt;
      pNew->pBoughtVehiclesList = pBoughtVehiclesList;

      const bool bPushResult = InsertToList(pCustomersList, (void*)pNew);

      if (!bPushResult)
      {
        FreeLinkedList(pBoughtVehiclesList);
        bReturn = false;
        goto End;
      }

      continue;
    }

    if (eSection == EMPLOYEE)
    {
      /* Parse ID, don't need to use fgets,
       * new line was already readed as it's in loop condition
       */
      for (size_t i = 0; i < strlen(line); i++)
      {
        if (!(*(line + i) >= '0' && *(line + i) <= '9') && (*(line + i) <= 0))
        {
          bReturn = false;
          goto End;
        }
      }

      unsigned short sEmployeeId = (unsigned short)atoi(line);

      // Parse first name
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      char szFirstName[101] = { 0 };
      StringCopy(line, szFirstName, sizeof(szFirstName));

      // Parse surname
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      char szSurname[101] = { 0 };
      StringCopy(line, szSurname, sizeof(line));

      // Parse date of birth
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      unsigned char cDateOfBirthDay = 0, cDateOfBirthMonth = 0;
      unsigned short sDateOfBirthYear = 0;

      int iDateOfBirthResult = sscanf(line, "%2hhu. %2hhu. %4hu", &cDateOfBirthDay, &cDateOfBirthMonth, &sDateOfBirthYear);

      if (iDateOfBirthResult != 3)
      {
        bReturn = false;
        goto End;
      }

      struct Date DateOfBirth = { 0 };
      InitDate(&DateOfBirth, cDateOfBirthDay, cDateOfBirthMonth, sDateOfBirthYear);

      // Parse employed until
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      unsigned char cEmployedUntilDay = 0, cEmployedUntilMonth = 0;
      unsigned short sEmployedUntilYear = 0;

      int iEmployedUntilResult = sscanf(line, "%2hhu. %2hhu. %4hu", &cEmployedUntilDay, &cEmployedUntilMonth, &sEmployedUntilYear);

      if (iEmployedUntilResult != 3)
      {
        bReturn = false;
        goto End;
      }

      struct Date dateEmployedUntil = { 0 };
      InitDate(&dateEmployedUntil, cEmployedUntilDay, cEmployedUntilMonth, sEmployedUntilYear);

      // Parse created at
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      unsigned char cCreatedAtDay = 0, cCreatedAtMonth = 0;
      unsigned short sCreatedAtYear = 0;

      int iCreatedAtResult = sscanf(line, "%2hhu. %2hhu. %4hu", &cCreatedAtDay, &cCreatedAtMonth, &sCreatedAtYear);

      if (iCreatedAtResult != 3)
      {
        bReturn = false;
        goto End;
      }

      struct Date dateCreatedAt = { 0 };
      InitDate(&dateCreatedAt, cCreatedAtDay, cCreatedAtMonth, sCreatedAtYear);

      // Parse sold vehicles
      struct LinkedList* pSoldVehiclesList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
      InitLinkedList(pSoldVehiclesList, NULL);
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      if (!strcmp(line, "null"))
      {
        /* If line is null do nothing, linked list of bought vehicles should be empty in this case.
         * Condition is needed because only valid values are "null", number (e. g. 123) or list (e. g. [1,2,3])
         */
      }
      else if (*line >= '0' && *line <= '9')
      {
        for (size_t i = 0; i < strlen(line); i++)
        {
          if (!(*(line + i) >= '0' && *(line + i) <= '9') && (*(line + i) != 0))
          {
            FreeLinkedList(pSoldVehiclesList);
            bReturn = false;
            goto End;
          }
        }

        unsigned short* pVehicleId = (unsigned short*)malloc(sizeof(unsigned short));
        *pVehicleId = (unsigned short)atoi(line);

        const bool bPushResult = InsertToList(pSoldVehiclesList, (void*)pVehicleId);

        if (!bPushResult)
        {
          FreeLinkedList(pSoldVehiclesList);
          bReturn = false;
          goto End;
        }
      }
      else if (*line == '[' && *(line + strlen(line) - 1) == ']')
      {
        unsigned char cNumbersCount = 0;

        for (size_t i = 0; i < strlen(line); i++)
        {
          if (*(line + i) == ',')
            cNumbersCount++;
        }

        if (cNumbersCount >= 1)
          cNumbersCount++;

        if (cNumbersCount == 0)
          goto SkipParsingListEmployee;

        unsigned char cCurrentCharacter = 0, cCurrentNumber = 0;
        char szVehicleId[6] = { 0 };
        unsigned short sVehicleIds[cNumbersCount];

        memset(sVehicleIds, 0, sizeof(sVehicleIds));

        for (size_t i = 1; i < strlen(line); i++)
        {
          char cCharacter = *(line + i);

          if (cCharacter == ',' || cCharacter == ']')
          {
            *(sVehicleIds + cCurrentNumber) = (unsigned short)atoi(szVehicleId);
            memset(szVehicleId, 0, sizeof(szVehicleId));
            cCurrentCharacter = 0;
            cCurrentNumber++;
          }

          else if (cCharacter >= '0' && cCharacter <= '9')
          {
            if (cCurrentCharacter >= sizeof(szVehicleId))
            {
              FreeLinkedList(pSoldVehiclesList);
              bReturn = false;
              goto End;
            }

            *(szVehicleId + cCurrentCharacter) = cCharacter;
            cCurrentCharacter++;
          }

          else
          {
            FreeLinkedList(pSoldVehiclesList);
            bReturn = false;
            goto End;
          }
        }

        for (size_t i = 0; i < cNumbersCount; i++)
        {
          unsigned short* pVehicleId = (unsigned short*)malloc(sizeof(unsigned short));
          *pVehicleId = *(sVehicleIds + i);

          const bool bPushResult = InsertToList(pSoldVehiclesList, (void*)pVehicleId);

          if (!bPushResult)
          {
            FreeLinkedList(pSoldVehiclesList);
            bReturn = false;
            goto End;
          }
        }
      }
      else
      {
        FreeLinkedList(pSoldVehiclesList);
        bReturn = false;
        goto End;
      }

SkipParsingListEmployee:
      // Check if next is \endEmployee
      fgets(line, sizeof(line), pFile);

      if (*(line + strlen(line) - 1) == '\n')
        *(line + strlen(line) - 1) = 0;

      if (strcmp(line, "\\endEmployee"))
      {
        FreeLinkedList(pSoldVehiclesList);
        bReturn = false;
        goto End;
      }

      // Add employee
      struct Employee* pNew = (struct Employee*)malloc(sizeof(struct Employee));

      pNew->sId = sEmployeeId;
      StringCopy(szFirstName, pNew->szFirstName, sizeof(pNew->szFirstName));
      StringCopy(szSurname, pNew->szSurname, sizeof(pNew->szSurname));
      pNew->DateOfBirth = DateOfBirth;
      pNew->dateEmployedUntil = dateEmployedUntil;
      pNew->dateCreatedAt = dateCreatedAt;
      pNew->pSoldVehiclesList = pSoldVehiclesList;

      const bool bPushResult = InsertToList(pEmployeesList, (void*)pNew);

      if (!bPushResult)
      {
        FreeLinkedList(pSoldVehiclesList);
        bReturn = false;
        goto End;
      }
    }
  }
End:
  if (!bReturn)
  {
    FreeVehicles();
    FreeCustomers();
    FreeEmployees();

    InitVehicle(NULL);
    InitCustomers(NULL);
    InitEmployees(NULL);
  }

  return bReturn;
}

void SaveDatabase(struct LinkedList* pVehiclesList, struct LinkedList* pCustomersList, struct LinkedList* pEmployeesList)
{
  CloseFile();

  if (!OpenWriteFile())
  {
    perror("Failed to open write file\n");
    return;
  }

  const char* szFileStart = "\\beginFile\n\n";
  const char* szFileEnd = "\\endFile";

  const char* szVehicleStart = "\\beginVehicle\n";
  const char* szVehicleEnd = "\\endVehicle\n\n";

  const char* szCustomerStart = "\\beginCustomer\n";
  const char* szCustomerEnd = "\\endCustomer\n\n";

  const char* szEmployeeStart = "\\beginEmployee\n";
  const char* szEmployeeEnd = "\\endEmployee\n\n";

  fwrite(szFileStart, sizeof(char), strlen(szFileStart), pFile);

  // Write vehicles
  void** ppVehicles = (void**)malloc(pVehiclesList->stCount * sizeof(void*));
  pVehiclesList->GetItemsAsArray(pVehiclesList->pStart, ppVehicles, pVehiclesList->stCount);

  for (void** i = ppVehicles; i < ppVehicles + pVehiclesList->stCount; i++)
  {
    struct Vehicle* pVehicle = (struct Vehicle*)*i;
    char szManufactionDate[11] = { 0 };
    FormatDate(pVehicle->ManufactionDate, szManufactionDate);

    char szSoldAt[13] = { 0 };
    FormatDate(pVehicle->dateSoldAt, szSoldAt);

    char szAddedAt[13] = { 0 };
    FormatDate(pVehicle->dateCreatedAt, szAddedAt);

    fwrite(szVehicleStart, sizeof(char), strlen(szVehicleStart), pFile);

    char szId[6] = { 0 };
    sprintf(szId, "%d", pVehicle->sId);
    fwrite(szId, sizeof(char), strlen(szId), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(pVehicle->szManufacturer, sizeof(char), strlen(pVehicle->szManufacturer), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(pVehicle->szModel, sizeof(char), strlen(pVehicle->szModel), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(pVehicle->szVin, sizeof(char), strlen(pVehicle->szVin), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(szManufactionDate, sizeof(char), strlen(szManufactionDate), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    char szKilometersDriven[11] = { 0 };
    sprintf(szKilometersDriven, "%d", pVehicle->iKilometersDriven);
    fwrite(szKilometersDriven, sizeof(char), strlen(szKilometersDriven), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(szAddedAt, sizeof(char), strlen(szAddedAt), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(pVehicle->bWasSold ? "yes" : "no", sizeof(char), strlen(pVehicle->bWasSold ? "yes" : "no"), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    char szEmployeeId[6] = { 0 };
    sprintf(szEmployeeId, "%d", pVehicle->sEmployeeId);
    fwrite(szEmployeeId, sizeof(char), strlen(szEmployeeId), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    char szCustomerId[6] = { 0 };
    sprintf(szCustomerId, "%d", pVehicle->sCustomerId);
    fwrite(szCustomerId, sizeof(char), strlen(szCustomerId), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(szSoldAt, sizeof(char), strlen(szSoldAt), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(szVehicleEnd, sizeof(char), strlen(szVehicleEnd), pFile);
  }

  free(ppVehicles);
  ppVehicles = NULL;

  // Write customers
  void** ppCustomers = (void**)malloc(pCustomersList->stCount * sizeof(void*));
  pCustomersList->GetItemsAsArray(pCustomersList->pStart, ppCustomers, pCustomersList->stCount);

  for (void** i = ppCustomers; i < ppCustomers + pCustomersList->stCount; i++)
  {
    struct Customer* pCustomer = (struct Customer*)*i;

    char szDateOfBirth[13] = { 0 };
    FormatDate(pCustomer->DateOfBirth, szDateOfBirth);

    char szCreatedAt[13] = { 0 };
    FormatDate(pCustomer->dateCreatedAt, szCreatedAt);

    fwrite(szCustomerStart, sizeof(char), strlen(szCustomerStart), pFile);

    char szId[6] = { 0 };
    sprintf(szId, "%d", pCustomer->sId);
    fwrite(szId, sizeof(char), strlen(szId), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(pCustomer->szFirstName, sizeof(char), strlen(pCustomer->szFirstName), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(pCustomer->szSurname, sizeof(char), strlen(pCustomer->szSurname), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(szDateOfBirth, sizeof(char), strlen(szDateOfBirth), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(szCreatedAt, sizeof(char), strlen(szCreatedAt), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    if (pCustomer->pBoughtVehiclesList->stCount == 0)
    {
      fwrite("null", sizeof(char), strlen("null"), pFile);
      fwrite("\n", sizeof(char), strlen("\n"), pFile);
    }

    if (pCustomer->pBoughtVehiclesList->stCount == 1)
    {
      char szVehicleId[6] = { 0 };
      sprintf(szVehicleId, "%d", *(unsigned short*)pCustomer->pBoughtVehiclesList->pStart->pData);
      fwrite(szVehicleId, sizeof(char), strlen(szVehicleId), pFile);
      fwrite("\n", sizeof(char), strlen("\n"), pFile);
    }

    if (pCustomer->pBoughtVehiclesList->stCount > 1)
    {
      void** ppBoughtVehicles = (void**)malloc(pCustomer->pBoughtVehiclesList->stCount * sizeof(void*));
      pCustomer->pBoughtVehiclesList->GetItemsAsArray(pCustomer->pBoughtVehiclesList->pStart, ppBoughtVehicles, pCustomer->pBoughtVehiclesList->stCount);

      fwrite("[", sizeof(char), strlen("["), pFile);

      for (size_t j = 0; j < pCustomer->pBoughtVehiclesList->stCount; j++)
      {
        unsigned short sId = **(unsigned short**)(ppBoughtVehicles + j);

        char szVehicleId[6] = { 0 };
        sprintf(szVehicleId, "%d", sId);
        fwrite(szVehicleId, sizeof(char), strlen(szVehicleId), pFile);

        if (j < pCustomer->pBoughtVehiclesList->stCount - 1)
          fwrite(",", sizeof(char), strlen(","), pFile);
      }

      free(ppBoughtVehicles);
      ppBoughtVehicles = NULL;

      fwrite("]", sizeof(char), strlen("]"), pFile);
      fwrite("\n", sizeof(char), strlen("\n"), pFile);
    }

    fwrite(szCustomerEnd, sizeof(char), strlen(szCustomerEnd), pFile);
  }

  free(ppCustomers);
  ppCustomers = NULL;

  // Write employees
  void** ppEmployees = (void**)malloc(pEmployeesList->stCount * sizeof(void*));
  pEmployeesList->GetItemsAsArray(pEmployeesList->pStart, ppEmployees, pEmployeesList->stCount);

  for (void** i = ppEmployees; i < ppEmployees + pEmployeesList->stCount; i++)
  {
    struct Employee* pEmployee = (struct Employee*)*i;

    char szDateOfBirth[13] = { 0 };
    FormatDate(pEmployee->DateOfBirth, szDateOfBirth);

    char szCreatedAt[13] = { 0 };
    FormatDate(pEmployee->dateCreatedAt, szCreatedAt);

    char szEmployedUntil[13] = { 0 };
    FormatDate(pEmployee->dateEmployedUntil, szEmployedUntil);

    fwrite(szEmployeeStart, sizeof(char), strlen(szEmployeeStart), pFile);

    char szId[6] = { 0 };
    sprintf(szId, "%d", pEmployee->sId);
    fwrite(szId, sizeof(char), strlen(szId), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(pEmployee->szFirstName, sizeof(char), strlen(pEmployee->szFirstName), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(pEmployee->szSurname, sizeof(char), strlen(pEmployee->szSurname), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(szDateOfBirth, sizeof(char), strlen(szDateOfBirth), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(szCreatedAt, sizeof(char), strlen(szCreatedAt), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    fwrite(szEmployedUntil, sizeof(char), strlen(szEmployedUntil), pFile);
    fwrite("\n", sizeof(char), strlen("\n"), pFile);

    if (pEmployee->pSoldVehiclesList->stCount == 0)
    {
      fwrite("null", sizeof(char), strlen("null"), pFile);
      fwrite("\n", sizeof(char), strlen("\n"), pFile);
    }

    if (pEmployee->pSoldVehiclesList->stCount == 1)
    {
      char szVehicleId[6] = { 0 };
      sprintf(szVehicleId, "%d", *(unsigned short*)pEmployee->pSoldVehiclesList->pStart->pData);
      fwrite(szVehicleId, sizeof(char), strlen(szVehicleId), pFile);
      fwrite("\n", sizeof(char), strlen("\n"), pFile);
    }

    if (pEmployee->pSoldVehiclesList->stCount > 1)
    {
      void** ppSoldVehicles = (void**)malloc(pEmployee->pSoldVehiclesList->stCount * sizeof(void*));
      pEmployee->pSoldVehiclesList->GetItemsAsArray(pEmployee->pSoldVehiclesList->pStart, ppSoldVehicles, pEmployee->pSoldVehiclesList->stCount);

      fwrite("[", sizeof(char), strlen("["), pFile);

      for (size_t j = 0; j < pEmployee->pSoldVehiclesList->stCount; j++)
      {
        unsigned short sId = **(unsigned short**)(ppSoldVehicles + j);

        char szVehicleId[6] = { 0 };
        sprintf(szVehicleId, "%d", sId);
        fwrite(szVehicleId, sizeof(char), strlen(szVehicleId), pFile);

        if (j < pEmployee->pSoldVehiclesList->stCount - 1)
          fwrite(",", sizeof(char), strlen(","), pFile);
      }

      free(ppSoldVehicles);
      ppSoldVehicles = NULL;

      fwrite("]", sizeof(char), strlen("]"), pFile);
      fwrite("\n", sizeof(char), strlen("\n"), pFile);
    }

    fwrite(szEmployeeEnd, sizeof(char), strlen(szEmployeeEnd), pFile);
  }

  free(ppEmployees);
  ppEmployees = NULL;

  fwrite(szFileEnd, sizeof(char), strlen(szFileEnd), pFile);

  CloseFile();
}
