#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <expat.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include "structures.h"
#include "display.h"
#include "calculations.h"
#define BUFF_SIZE 500000

static int depth = 0;
/*
 *  ALOKOWANIE PAMIĘCI
 */
void pathInit () {
    path = calloc(1, sizeof(PtList));
}

void pathFree () {
    free(path -> point);
    free(path -> date);
    free(path -> height);
}

/*
 *  PARSOWANIE
 */
void start_element (void *data, const char *element, const char **attribute) {
    if(!strcmp(element, "trkpt")) {
        path -> point = realloc(path -> point, (path -> pointsNum + 1) * sizeof(Pt));
        path -> point[path -> pointsNum].lat = atofC(attribute[1]);
        path -> point[path -> pointsNum].lon = atofC(attribute[3]);
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
                char dateStr [len];
                strncpy(dateStr, object, len);
                path -> date = realloc(path -> date, (path -> dateNum + 1) * sizeof(PtDate));
                getDate(path -> date, path -> dateNum, dateStr);
                path -> dateNum++;
            }
        }
        else if(object[len + 2] == 'e'){
            char heightStr [len];
            strncpy(heightStr, object, len);
            path -> height = realloc(path -> height, (path -> hNum + 1) * sizeof(double));
            path -> height[path -> hNum] = atofC(heightStr);
            path -> hNum++;
        }
    }
}

bool pathParse (const char *fileName) {
    FILE *fp;
    
    if ((fp = fopen(fileName, "r")) == NULL) {
        return 1;
    }

    pathInit();
    char *buff = malloc(BUFF_SIZE);

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