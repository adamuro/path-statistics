#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct date {
    unsigned short day, month, year;
    unsigned short hour, minute, second;
} date;

typedef struct Pt {
    double lat;
    double lon;
} Pt;

typedef struct PtList {
	int pointsNum;
	Pt *point;

	int dateNum;
	date *pDate;

	int hNum;
	double *height;
} PtList;

#endif