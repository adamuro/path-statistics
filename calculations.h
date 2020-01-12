#include "structures.h"
#ifndef CALCULATIONS_H
#define CALCULATIONS_H

double atofCoord (const char *str);

double singleDistance (point point1, point point2);

double fullDistance (point *path, int pointsNum);

#endif