#include "calculations.h"

double atofC (const char *Str) {
	double Number = 0;
	double Div = 10;
	int i;
	for(i = 0 ; Str[i] != '.' ; i++) {
		Number *= 10;
		Number += Str[i] - 48;
	}
	while(++i < strlen(Str)) {
		Number += ((double)Str[i] - 48) / Div;
		Div *= 10;
	}
	return Number;
}

char* cutFileName(char *Source) {
	static char fileName[100];
	for(int i = 0 ; i < strlen(Source) ; i++) {
		if(Source[i] == '/')
			strncpy(fileName, Source + i + 1, strlen(Source) - i);
	}
	return fileName;
}

double singleDistance (Pt p1, Pt p2) {
    double Dist = 6371.0 * acos(sin(p1.lat / 180.0 * M_PI) * sin(p2.lat / 180.0 * M_PI) +
        cos(p1.lat / 180.0 * M_PI) * cos(p2.lat / 180.0 * M_PI) *
        cos(p1.lon / 180.0 * M_PI - p2.lon / 180.0 * M_PI));
    if(!isnan(Dist)) {
    	return Dist;
    }
    return 0;
}

double fullDistance () {
    double fullDist = 0;
    for(int i = 1 ; i < Path -> pointsNum ; i++) {
        fullDist += singleDistance(Path -> Point[i - 1], Path -> Point[i]);
    }
    return fullDist;
}

double minHeight () {
	double minH = Path -> Height[0];
	for(int i = 1 ; i < Path -> hNum ; i++) {
		if(Path -> Height[i] < minH)
			minH = Path -> Height[i];
	}
	return minH;
}

double maxHeight () {
	double maxH = Path -> Height[0];
	for(int i = 1 ; i < Path -> hNum ; i++) {
		if(Path -> Height[i] > maxH)
			maxH = Path -> Height[i];
	}
	return maxH;
}

double heightDif () {
    return maxHeight(Path) - minHeight(Path);
}

void getDate (PtDate *Date, int dateNum, char *dateStr) {
	char dateMember[4];
	strncpy(dateMember, dateStr, 4);
	Date[dateNum].year = atoi(dateMember);
	dateMember[2] = dateMember[3] = '\0';
	strncpy(dateMember, dateStr + 5, 2);
	Date[dateNum].month = atoi(dateMember);
	strncpy(dateMember, dateStr + 8, 2);
	Date[dateNum].day = atoi(dateMember);
	strncpy(dateMember, dateStr + 11, 2);
	Date[dateNum].hour = atoi(dateMember);
	strncpy(dateMember, dateStr + 14, 2);
	Date[dateNum].minute = atoi(dateMember);
	strncpy(dateMember, dateStr + 17, 2);
	Date[dateNum].second = atoi(dateMember);
}

bool leapYear (int Year) {
	if((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0)
		return 1;
	return 0;
}

int daysTillMonth (PtDate Date) {
	int daysNum[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int Days = 0;
	if(leapYear(Date.year))
		daysNum[1]++;
	for(int i = 0 ; i < Date.month ; i++) {
		Days += daysNum[i];
	}
	return Days;
}

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

long long PathDuration () {
	return timeDifference(Path -> Date[0], Path -> Date[Path -> dateNum - 1]);
}

double singleSpeed (int startPointIndex, int endPointIndex) {
	return singleDistance(Path -> Point[startPointIndex], Path -> Point[endPointIndex])
		/ ((double)timeDifference(Path -> Date[startPointIndex], Path -> Date[endPointIndex]) / 3600);
}

double averageSpeed () {
	return fullDistance() / ((double)PathDuration() / 3600);
}

double maxSpeed () {
	double maxSpeed = 0;
	double tempSpeed;

	for(int i = 1 ; i < Path -> pointsNum ; i++) {
		tempSpeed = singleDistance(Path -> Point[i - 1], Path -> Point[i])
			/ ((double)timeDifference(Path -> Date[i - 1], Path -> Date[i]) / 3600);
		if(tempSpeed > maxSpeed && tempSpeed != INFINITY)
			maxSpeed = tempSpeed;
	}
	return maxSpeed;
}

double minSpeed () {
	double tempSpeed;
	double minSpeed = singleDistance(Path -> Point[0], Path -> Point[1])
			/ ((double)timeDifference(Path -> Date[0], Path -> Date[1]) / 3600);

	for(int i = 2 ; i < Path -> pointsNum ; i++) {
		tempSpeed = singleDistance(Path -> Point[i - 1], Path -> Point[i])
			/ ((double)timeDifference(Path -> Date[i - 1], Path -> Date[i]) / 3600);
		if(tempSpeed < minSpeed && tempSpeed != INFINITY && tempSpeed > 0)
			minSpeed = tempSpeed;
	}
	return minSpeed;
}

double maxTempo () {
	return 1 / maxSpeed() * 60;
}

double minTempo () {
	return 1 / minSpeed() * 60;
}

double averageTempo () {
	return 1 / averageSpeed() * 60;
}

double convertToCartesianY (Pt Point) {
	return R * cos(Point.lat * M_PI * 2.0 / 360.0) * cos(Point.lon * M_PI * 2.0 / 360.0);
}

double convertToCartesianX (Pt Point) {
	return R * cos(Point.lat * M_PI * 2.0 / 360.0) * sin(Point.lon * M_PI * 2.0 / 360.0);
}

void cartesianMinimums (double *minCartesianX, double *minCartesianY, Pt *Point, int pointsNum) {
	*minCartesianX = convertToCartesianX(Point[0]);
	*minCartesianY = convertToCartesianY(Point[0]);

	for(int i = 1 ; i < pointsNum ; i++) {
		double cartesianX = convertToCartesianX(Point[i]);
		double cartesianY = convertToCartesianY(Point[i]);
		if(cartesianX < *minCartesianX)
			*minCartesianX = cartesianX;
		if(cartesianY < *minCartesianY)
			*minCartesianY = cartesianY;
	}
}

void cartesianDiffs (double minX, double minY, double *difX, double *difY, Pt *Point, int pointsNum) {
	double maxCartesianX = convertToCartesianX(Point[0]);
	double maxCartesianY = convertToCartesianY(Point[0]);
	for(int i = 1 ; i < pointsNum ; i++) {
		double cartesianX = convertToCartesianX(Point[i]);
		if(cartesianX > maxCartesianX)
			maxCartesianX = cartesianX;
		double cartesianY = convertToCartesianY(Point[i]);
		if(cartesianY > maxCartesianY)
			maxCartesianY = cartesianY;
	}
	*difX = maxCartesianX - minX;
	*difY = maxCartesianY - minY;
}