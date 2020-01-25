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

double maxTempo ();

double minTempo ();

double averageTempo ();

double convertToCartesianX (Pt point);

double convertToCartesianY (Pt point);

double minCartesianX (Pt *point, int pointsNum);

double minCartesianY (Pt *point, int pointsNum);

double cartesianDifX (Pt *point, int pointsNum);

double cartesianDifY (Pt *point, int pointsNum);

#endif