#include "structures.h"
#ifndef LOADING_H
#define LOADING_H

void start_element (void *data, const char *element, const char **attribute);

void end_element (void *data, const char *el);

int xmlParse (const char *fileName);

double fullDistancePass (point *path, int pointsNum);

double fullDistance ();

#endif