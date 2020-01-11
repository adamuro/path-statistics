#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <expat.h>
#include <gtk/gtk.h>
#include "structures.h"
#include "display.h"
#include "calculations.h"
#define BUFF_SIZE 100000

static int depth = 0;

point *path;

int pointsNum = 0;

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

int xmlParse (const char *fileName) {
    FILE *fp;
    if ((fp = fopen(fileName, "r")) == NULL) {
        fileOpenError();
        return 1;
    }
    path = calloc(1, sizeof(point));

    char *buff = malloc(BUFF_SIZE);

    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);

    fread(buff, sizeof(char), BUFF_SIZE, fp);

    XML_Parse(parser, buff, strlen(buff), XML_TRUE);

    fclose(fp);
    free(buff);
    XML_ParserFree(parser);
    return 0;
}

double fullDistance () {
    double dist = fullDistancePass(path, pointsNum);
    pointsNum = 0;
    return dist;
}