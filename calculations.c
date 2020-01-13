#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structures.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void copyStrPart (char *str, char *src, int startPos, int charNum) {
	for(int i = 0 ; i < charNum ; i++)
		str[i] = src[startPos + i];
}

double atofCoord (const char *str) {
	double coord = 0;
	double div = 10;
	int i;
	for(i = 0 ; str[i] != '.' ; i++) {
		coord *= 10;
		coord += str[i] - 48;
	}
	while(++i < strlen(str) - 1) {
		coord += ((double)str[i] - 48) / div;
		div *= 10;
	}
	return coord;
}

void getDate(date pDate, char *dateStr) {
	char year [4];
	char dateMember [2];
	copyStrPart(year, dateStr, 0, 4);
	copyStrPart(dateMember, dateStr, 5, 2);
}

double singleDistance (Pt p1, Pt p2) {
    double dist = 6371.0 * acos(sin(p1.lat / 180.0 * M_PI) * sin(p2.lat / 180.0 * M_PI) +
        cos(p1.lat / 180.0 * M_PI) * cos(p2.lat / 180.0 * M_PI) *
        cos(p1.lon / 180.0 * M_PI - p2.lon / 180.0 * M_PI));
    return dist;
}

double fullDistance (PtList *path) {
    double fullDist = 0;
    for(int i = 1 ; i < path -> pointsNum ; i++) {
        fullDist += singleDistance(path -> point[i - 1], path -> point[i]);
    }
    return fullDist;
}

double minHeight (PtList *path) {
	double minH = path -> height[0];
	for(int i = 1 ; i < path -> hNum ; i++) {
		if(path -> height[i] < minH)
			minH = path -> height[i];
	}
	return minH;
}

double maxHeight (PtList *path) {
	double maxH = path -> height[0];
	for(int i = 1 ; i < path -> hNum ; i++) {
		if(path -> height[i] > maxH)
			maxH = path -> height[i];
	}
	return maxH;
}