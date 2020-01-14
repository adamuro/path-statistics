#ifndef PARSING_H
#define PARSING_H

void pathFree ();

void start_element (void *data, const char *element, const char **attribute);

void end_element (void *data, const char *el);

int pathParse (const char *fileName);

#endif