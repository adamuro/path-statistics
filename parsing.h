#ifndef PARSING_H
#define PARSING_H

void start_element (void *data, const char *element, const char **attribute);

void end_element (void *data, const char *el);

int xmlParse (const char *fileName);

double fullDistancePass ();

double minHeightPass ();

double maxHeightPass ();

double heightDif ();

#endif