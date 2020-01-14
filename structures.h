#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct PtDate {
    unsigned short day, month, year;
    unsigned short hour, minute, second;
} PtDate;

typedef struct Pt {
    double lat;
    double lon;
} Pt;

typedef struct PtList {
	int pointsNum;
	Pt *point;

	int dateNum;
	PtDate *date;

	int hNum;
	double *height;
} PtList;

PtList *path;

#endif