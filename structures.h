#ifndef STRUCTURES_H
#define STRUCTURES_H

/* DATE */
typedef struct PtDate {
    unsigned short day, month, year;
    unsigned short hour, minute, second;
} PtDate;
/* GEOGRAPHIC COORDINATES */
typedef struct Pt {
    double lat;
    double lon;
} Pt;
/* INFORMATIONS ABOUT A SINGLE POINT */
typedef struct PtList {
	int pointsNum;
	Pt *Point;

	int dateNum;
	PtDate *Date;

	int hNum;
	double *Height;
} PtList;

PtList *Path;

#endif