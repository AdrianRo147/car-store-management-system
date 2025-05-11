#ifndef DATE_H
#define DATE_H

#include <stdbool.h>

struct Date
{
  unsigned char cDay;
  unsigned char cMonth;
  unsigned short sYear;
};

extern void InitDate(struct Date* pDate, unsigned char cDay, unsigned char cMonth, unsigned short sYear);
extern void FormatDate(struct Date date, char* szDst);
extern void SetCurrentDate(struct Date* pDate);
extern bool IsNullDate(struct Date date);

#endif
