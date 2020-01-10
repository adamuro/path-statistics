#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct date {
    unsigned short day, month, year;
    unsigned short hour, minute, second;
} date;

typedef struct point {
    double lat;
    double lon;
    double height;
    date pDate;
} point;

#endif