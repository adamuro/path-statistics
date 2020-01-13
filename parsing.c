#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <expat.h>
#include <gtk/gtk.h>
#include <limits.h>
#include "structures.h"
#include "display.h"
#include "calculations.h"
#define BUFF_SIZE 500000

static int depth = 0;

PtList *path;

void pathInit () {
    path = calloc(1, sizeof(PtList));
}

void pathFree () {
    path -> pointsNum = 0;
    free(path -> point);
    path -> dateNum = 0;
    free(path -> pDate);
    path -> hNum = 0;
    free(path -> height);
}

void start_element (void *data, const char *element, const char **attribute) {
    if(!strcmp(element, "trkpt")) {
        path -> point = realloc(path -> point, (path -> pointsNum + 1) * sizeof(Pt));
        path -> point[path -> pointsNum].lat = atofCoord(attribute[1]);
        path -> point[path -> pointsNum].lon = atofCoord(attribute[3]);
        path -> pointsNum++;
    }
    depth++;
}

void end_element (void *data, const char *el) {
    depth--;
}

void handler(void *data, const char *object, int len) {
    if(depth == 5) {
        if(object[len + 2] == 't') {
            char dateCheck[4];
            strncpy(dateCheck, object + len + 2, 4);
            if(!strcmp(dateCheck, "time")) {
                char dateStr [len - 1];
                strncpy(dateStr, object, len - 1);
                path -> pDate = realloc(path -> pDate, (path -> dateNum + 1) * sizeof(date));
                getDate(path -> pDate[path -> dateNum], dateStr);
                path -> dateNum++;
            }
        }
        else if(object[len + 2] == 'e'){
            char heightStr [len - 3];
            strncpy(heightStr, object, len - 3);
            path -> height = realloc(path -> height, (path -> hNum + 1) * sizeof(double));
            path -> height[path -> hNum] = atofCoord(heightStr);
            path -> hNum++;
        }
    }
}

int xmlParse (const char *fileName) {
    FILE *fp;
    if ((fp = fopen(fileName, "r")) == NULL) {
        fileOpenError();
        return 1;
    }
    char *buff = malloc(BUFF_SIZE);
    pathInit();

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
    return fullDistance(path);
}

double minHeightPass () {
    return minHeight(path);
}

double maxHeightPass () {
    return maxHeight(path);
}

double heightDif () {
    return maxHeight(path) - minHeight(path);
}