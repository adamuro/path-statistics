#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structures.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double atofCoord (const char *str) {
	double coord = 0;
	double div = 10;
	int i;
	for(i = 0 ; str[i] != '.' ; i++) {
		coord *= 10;
		coord += str[i] - 48;
	}
	while(i++ < strlen(str)) {
		coord += ((double)str[i] - 48) / div;
		div *= 10;
	}
	return coord;
}

double singleDistance (point point1, point point2) {
    double dist = 6371.0 * acos(sin(point1.lon / 180.0 * M_PI) * sin(point2.lon / 180.0 * M_PI) +
        cos(point1.lon / 180.0 * M_PI) * cos(point2.lon / 180.0 * M_PI) *
        cos(point2.lat / 180.0 * M_PI - point1.lat / 180.0 * M_PI));
    return dist;
}

double fullDistancePass (point *path, int pointsNum) {
    double fullDist = 0;
    for(int i = 1 ; i < pointsNum ; i++) {
        fullDist += singleDistance(path[i - 1], path[i]);
    }
    return fullDist;
}