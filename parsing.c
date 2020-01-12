#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <expat.h>
#include <gtk/gtk.h>
#include "structures.h"
#include "display.h"
#include "calculations.h"
#define BUFF_SIZE 500000

static int depth = 0;

point *path;
int pointsNum = 0;
double maxHeight = 0;
double minHeight = 999999;

void start_element (void *data, const char *element, const char **attribute) {
    if(!strcmp(element, "trkpt")) {
        path = realloc(path, (pointsNum + 1) * sizeof(point));
        path[pointsNum].lat = atofCoord(attribute[1]);
        path[pointsNum].lon = atofCoord(attribute[3]);
        pointsNum++;
    }
    depth++;
}

void end_element (void *data, const char *el) {
    depth--;
}

void handler(void *data, const char *object, int len) {
    //if() {
    // WCZYTYWANIE DATY
    //}
    char ele[3];
    strncpy(ele, object + len + 2, 3);
    if(!strcmp(ele, "ele")) {
        char h [len - 3];
        strncpy(h, object, len - 3);
        double height = atofCoord(h);
        if(height > maxHeight)
            maxHeight = height;
        else if(height < minHeight)
            minHeight = height;
    }
}

int xmlParse (const char *fileName) {
    FILE *fp;
    if ((fp = fopen(fileName, "r")) == NULL) {
        fileOpenError();
        return 1;
    }
    char *buff = malloc(BUFF_SIZE);
    path = calloc(1, sizeof(point));

    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handler);

    fread(buff, sizeof(char), BUFF_SIZE, fp);

    XML_Parse(parser, buff, strlen(buff), XML_TRUE);

    fclose(fp);
    free(buff);
    XML_ParserFree(parser);
    return 0;
}

double fullDistancePass () {
    double dist = fullDistance(path, pointsNum);
    pointsNum = 0;
    return dist;
}

double minHeightPass () {
    return minHeight;
}

double maxHeightPass () {
    return maxHeight;
}

double heightDif () {
    double minH = minHeight;
    double maxH = maxHeight;
    minHeight = 999999;
    maxHeight = 0;
    return maxH - minH;
}