#ifndef CALCULATIONS_H
#define CALCULATIONS_H 

#define M_PI 3.14159265358979323846
#define R 6371

#include "common.h"

double atofC (const char *Str); // Standard atof didn't work
double singleDistance (Pt p1, Pt p2); // Between 2 points
double fullDistance ();
double minHeight ();
double maxHeight ();
double heightDif ();
void getDate (PtDate *Date, int dateNum, char *dateStr); // Read date from GPX format and save in the Date struct
bool leapYear (int Year); // Is Year a leap year?
int daysTillMonth (PtDate Date); // Number of days between 01.01 and first day of the month
long long timeDifference (PtDate startDate, PtDate endDate); // Number of seconds between 2 dates
long long PathDuration (); // In seconds
double singleSpeed (int startPointIndex, int endPointIndex); // In km/h
double averageSpeed ();
double maxSpeed ();
double minSpeed ();
double averageTempo (); // In min/km
double maxTempo ();
double minTempo ();
double convertToCartesianX (Pt Point); // Conversion from geographic to cartesian coordinates for the X axis
double convertToCartesianY (Pt Point); // Conversion from geographic to cartesian coordinates for the Y axis
void cartesianMinimums
	(double *minCartesianX, double *minCartesianY, Pt *Point, int pointsNum); // Find minimal x and y coordinates and assign them to pointers
void cartesianDiffs 
	(double minX, double minY, double *difX, double *difY,
	Pt *Point, int pointsNum); // Calculate the differences between maximal and minimal x and y coordinates and assign them to pointers

#endif