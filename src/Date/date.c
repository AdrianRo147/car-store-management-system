#include "date.h"

#include <stdio.h>
#include <time.h>

void InitDate(struct Date* pDate, unsigned char cDay, unsigned char cMonth, unsigned short sYear)
{
  pDate->cDay = cDay;
  pDate->cMonth = cMonth;
  pDate->sYear = sYear;
}

void FormatDate(struct Date date, char* szDst)
{
  sprintf(szDst, "%d. %d. %d", date.cDay, date.cMonth, date.sYear);
}

void SetCurrentDate(struct Date* pDate)
{
  time_t CurrentTime;
  time(&CurrentTime);

  const struct tm* const pTime = localtime(&CurrentTime);

  pDate->cDay = pTime->tm_mday;
  pDate->cMonth = pTime->tm_mon + 1;
  pDate->sYear = pTime->tm_year + 1900;
}

bool IsNullDate(struct Date date)
{
  return date.cDay == 0 && date.cMonth == 0 && date.sYear == 0;
}
