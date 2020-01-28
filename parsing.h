#ifndef PARSING_H
#define PARSING_H

#define BUFF_SIZE 500000

#include "common.h"

void pathInit (); // Allocate memory for a new path and fill it with zeros
void pathFree (); // Free the allocated mamory
void startElement (void *Data, const char *Element, const char **Attribute); // Find geographic coordinates in the GPX file
void endElement (void *Data, const char *Elelement);
void Handler(void *Data, const char *Object, int Length); // Find dates and heights in the GPX file
bool PathParse (const char *fileName); // Check if given file exists, set up a parser and read needed informations

#endif