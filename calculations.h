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

long long timeDifference (PtDate startDate, PtDate endDate);

long long pathDuration ();

double singleSpeed (int startPointIndex, int endPointIndex);

double averageSpeed ();

double maxSpeed ();

double minSpeed ();

double averageTempo ();

#endif