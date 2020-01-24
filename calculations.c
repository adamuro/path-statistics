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
	while(++i < strlen(str)) {
		coord += ((double)str[i] - 48) / div;
		div *= 10;
	}
	return coord;
}
/*
 *	ODLEGŁOŚĆ MIĘDZY DWOMA PUNKTAMI
 */
double singleDistance (Pt p1, Pt p2) {
    double dist = 6371.0 * acos(sin(p1.lat / 180.0 * M_PI) * sin(p2.lat / 180.0 * M_PI) +
        cos(p1.lat / 180.0 * M_PI) * cos(p2.lat / 180.0 * M_PI) *
        cos(p1.lon / 180.0 * M_PI - p2.lon / 180.0 * M_PI));
    if(!isnan(dist)) {
    	//printf("%lf %lf %lf\n", p1.lat, p1.lon, dist);
    	return dist;
    }
    return 0;
}
/*
 *  DYSTANS CAŁEJ TRASY
 */
double fullDistance () {
    double fullDist = 0;
    for(int i = 1 ; i < path -> pointsNum ; i++) {
        fullDist += singleDistance(path -> point[i - 1], path -> point[i]);
        //printf("%lf\n", fullDist);
    }
    //printf("full dist: %lf\n", fullDist);
    return fullDist;
}
/*
 *	NAJNIŻSZY PUNKT
 */
double minHeight () {
	double minH = path -> height[0];
	for(int i = 1 ; i < path -> hNum ; i++) {
		if(path -> height[i] < minH)
			minH = path -> height[i];
	}
	return minH;
}
/*
 *  NAJWYŻSZY PUNKT
 */
double maxHeight () {
	double maxH = path -> height[0];
	for(int i = 1 ; i < path -> hNum ; i++) {
		if(path -> height[i] > maxH)
			maxH = path -> height[i];
	}
	return maxH;
}
/*
 *  RÓŻNICA MIĘDZY NAJWYŻSZYM I NAJNIŻSZYM PUNKTEM
 */
double heightDif () {
    return maxHeight(path) - minHeight(path);
}
/*
 *	ODCZYTANIE POJEDYNCZEJ DATY Z PLIKU GPX
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
/*
 *  CZY ROK JEST PRZESTĘPNY
 */
bool leapYear (int year) {
	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 1;
	return 0;
}
/*
 *  LICZBA DNI OD POCZĄTKU ROKU DO MIESIĄCA
 */
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
/*
 * ROZNICA CZASU MIĘDZY DWOMA PUNKTAMI W SEKUNDACH
 */
long long timeDifference (PtDate startDate, PtDate endDate) {
	long long timeDifference = 0;
	for(int i = startDate.year ; i < endDate.year ; i++)
		timeDifference += (leapYear(i)) ? 366 * 24 * 3600 : 365 * 24 * 3600;
	timeDifference += daysTillMonth(endDate) * 24 * 3600 +
				(endDate.day - 1) * 24 * 3600 + endDate.hour * 3600 +
				endDate.minute * 60 + endDate.second;
	timeDifference -= daysTillMonth(startDate) * 24 * 3600 +
				(startDate.day - 1) * 24 * 3600 + startDate.hour * 3600 +
				startDate.minute * 60 + startDate.second;
	return timeDifference;
}
/*
 *  CZAS TRWANIA TRASY
 */
long long pathDuration () {
	return timeDifference(path -> date[0], path -> date[path -> dateNum - 1]);
}
/*
 *  PRĘDKOŚĆ MIĘDZY DWOMA PUNKTAMI
 */
double singleSpeed (int startPointIndex, int endPointIndex) {
	return singleDistance(path -> point[startPointIndex], path -> point[endPointIndex])
		/ ((double)timeDifference(path -> date[startPointIndex], path -> date[endPointIndex]) / 3600);
}
/*
 *  ŚREDNIA PRĘDKOŚĆ
 */
double averageSpeed () {
	return fullDistance() / ((double)pathDuration() / 3600);
}
/*
 *  NAJWYŻSZA PRĘDKOŚĆ
 */
double maxSpeed () {
	double maxSpeed = 0;
	double tempSpeed;
/*	double tempDist;
	double tempTime;
	double tempSpeed;

	for(int i = 3 ; i < path -> pointsNum ; i++) {
		tempDist = 0;
		tempTime = timeDifference(path -> date[i - 3], path -> date[i]);
		for(int j = 3 ; j > 0 ; j--) {
			tempDist += singleDistance(path -> point[i - j], path -> point[i - j + 1]);
		}
		tempSpeed = tempDist / (tempTime / 3600);
		if(tempSpeed > maxSpeed)
			maxSpeed = tempSpeed;
	}
	return maxSpeed;
	*/
	//printf("%d %d %d\n", path -> pointsNum, path -> hNum, path -> dateNum);
	for(int i = 1 ; i < path -> pointsNum ; i++) {
		//printf("1. single dist. %lf\n", singleDistance(path -> point[i - 1], path -> point[i]));
		//printf("2. time dif. %lf\n", (double)timeDifference(path -> date[i - 1], path -> date[i]) / 3600);
		//printf("3. date %d %d %d\n", path -> date[i].hour, path -> date[i].minute, path -> date[i].second);
		tempSpeed = singleDistance(path -> point[i - 1], path -> point[i])
			/ ((double)timeDifference(path -> date[i - 1], path -> date[i]) / 3600);
		if(tempSpeed > maxSpeed && tempSpeed != INFINITY)
			maxSpeed = tempSpeed;
		printf("4. max v %lf\n", maxSpeed);
	}
	printf(". max v %lf\n", maxSpeed);
	return maxSpeed;
}
/*
 *  NAJNIŻSZA PRĘDKOŚĆ
 */
double minSpeed () {
	double minSpeed = maxSpeed();
	double tempDist;
	double tempTime;
	double tempSpeed;

	for(int i = 3 ; i < path -> pointsNum ; i++) {
		tempDist = 0;
		tempTime = timeDifference(path -> date[i - 3], path -> date[i]);
		for(int j = 3 ; j > 0 ; j--) {
			double isMoving = singleDistance(path -> point[i - j], path -> point[i - j + 1]);
			if(isMoving)
				tempDist += isMoving;
		}
		tempSpeed = tempDist / (tempTime / 3600);
		if(tempSpeed < minSpeed && tempSpeed != 0)
			minSpeed = tempSpeed;
	}
	return minSpeed;
}
/*
 *  NAJWYŻSZE TEMPO
 */
double maxTempo () {
	return 1 / maxSpeed() * 60;
}
/*
 *  NAJNIŻSZE TEMPO
 */
double minTempo () {
	return 1 / minSpeed() * 60;
}
/*
 *  ŚREDNIE TEMPO
 */
double averageTempo () {
	return 1 / averageSpeed() * 60;
}