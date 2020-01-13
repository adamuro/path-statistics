#include "structures.h"
#ifndef CALCULATIONS_H
#define CALCULATIONS_H

char* copyStrPart (char *str, int from, int to);

double atofCoord (const char *str);

void getDate(date pDate, char *dateStr);

double singleDistance (Pt p1, Pt p2);

double fullDistance (PtList *path);

double minHeight (PtList *path);

double maxHeight (PtList *path);

#endif