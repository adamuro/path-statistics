#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "structures.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
/* Standardowy atof nie działa */
double atofC (const char *str) {
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
/*
 *	ODLEGŁOŚCI
 */
double singleDistance (Pt p1, Pt p2) {
    double dist = 6371.0 * acos(sin(p1.lat / 180.0 * M_PI) * sin(p2.lat / 180.0 * M_PI) +
        cos(p1.lat / 180.0 * M_PI) * cos(p2.lat / 180.0 * M_PI) *
        cos(p1.lon / 180.0 * M_PI - p2.lon / 180.0 * M_PI));
    return dist;
}

double fullDistance () {
    double fullDist = 0;
    for(int i = 1 ; i < path -> pointsNum ; i++) {
        fullDist += singleDistance(path -> point[i - 1], path -> point[i]);
    }
    return fullDist;
}
/*
 *	WYSOKOŚCI
 */
double minHeight () {
	double minH = path -> height[0];
	for(int i = 1 ; i < path -> hNum ; i++) {
		if(path -> height[i] < minH)
			minH = path -> height[i];
	}
	return minH;
}

double maxHeight () {
	double maxH = path -> height[0];
	for(int i = 1 ; i < path -> hNum ; i++) {
		if(path -> height[i] > maxH)
			maxH = path -> height[i];
	}
	return maxH;
}

double heightDif () {
    return maxHeight(path) - minHeight(path);
}
/*
 *	DATY
 */
void getDate (PtDate *date, int dateNum, char *dateStr) {
	char dateMember[4];
	strncpy(dateMember, dateStr, 4);
	date[dateNum].year = atoi(dateMember);
	dateMember[2] = dateMember[3] = '\0';
	strncpy(dateMember, dateStr + 5, 2);
	date[dateNum].month = atoi(dateMember);
	strncpy(dateMember, dateStr + 8, 2);
	date[dateNum].day = atoi(dateMember);
	strncpy(dateMember, dateStr + 11, 2);
	date[dateNum].hour = atoi(dateMember);
	strncpy(dateMember, dateStr + 14, 2);
	date[dateNum].minute = atoi(dateMember);
	strncpy(dateMember, dateStr + 17, 2);
	date[dateNum].second = atoi(dateMember);
}

bool leapYear (int year) {
	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 1;
	return 0;
}

int daysTillMonth (PtDate date) {
	int daysNum[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int days = 0;
	if(leapYear(date.year))
		daysNum[1]++;
	for(int i = 0 ; i < date.month ; i++) {
		days += daysNum[i];
	}
	return days;
}
/* ROZNICA CZASU MIĘDZY DWOMA PUNKTAMI W SEKUNDACH */
long long timeDifference (PtDate startDate, PtDate endDate) {
	long long timeDifference = 0;
	for(int i = startDate.year ; i < endDate.year ; i++)
		timeDifference += (leapYear(i)) ? 366 * 24 * 3600 : 365 * 24 * 3600;
	timeDifference += daysTillMonth(endDate) * 24 * 3600 +
				endDate.day * 24 * 3600 + endDate.hour * 3600 +
				endDate.minute * 60 + endDate.second;
	timeDifference -= daysTillMonth(startDate) * 24 * 3600 +
				startDate.day * 24 * 3600 + startDate.hour * 3600 +
				startDate.minute * 60 + startDate.second;
	return timeDifference;
}

long long pathDuration () {
	return timeDifference(path -> date[0], path -> date[path -> dateNum - 1]);
}

double singleSpeed (int startPointIndex, int endPointIndex) {
	return singleDistance(path -> point[startPointIndex], path -> point[endPointIndex])
		/ ((double)timeDifference(path -> date[startPointIndex], path -> date[endPointIndex]) / 3600);
}

double averageSpeed () {
	return fullDistance() / ((double)pathDuration() / 3600);
}

double maxSpeed () {
	double maxSpeed = singleSpeed(0, 1);
	for(int i = 2 ; i < path -> pointsNum ; i++) {
		if(singleSpeed(i - 1, i) > maxSpeed && singleSpeed(i - 1, i) != INFINITY) {
			maxSpeed = singleSpeed(i - 1, i);
		}
	}
	return maxSpeed;
}

double minSpeed () {
	double minSpeed = singleSpeed(0, 1);
	for(int i = 2 ; i < path -> pointsNum ; i++) {
		if(singleSpeed(i - 1, i) < minSpeed && singleSpeed(i - 1, i) != 0) {
			minSpeed = singleSpeed(i - 1, i);
		}
	}
	return minSpeed;
}

double averageTempo () {
	return 1 / averageSpeed() * 60;
}