#include "structures.h"
#ifndef CALCULATIONS_H
#define CALCULATIONS_H

double atofC (const char *str);

double singleDistance (Pt p1, Pt p2);

double fullDistance ();

double minHeight ();

double maxHeight ();

double heightDif ();

void getDate (PtDate *date, int dateNum, char *dateStr);

long long pathDuration ();

#endif