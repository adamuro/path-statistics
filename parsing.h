#ifndef PARSING_H
#define PARSING_H

#define BUFF_SIZE 500000

#include "common.h"

void pathInit ();

void pathFree ();

void start_element (void *data, const char *element, const char **attribute);

void end_element (void *data, const char *el);

bool pathParse (const char *fileName);

#endif