#include "calculations.h"
#ifndef LOADING_H
#define LOADING_H

void start_element(void *data, const char *element, const char **attribute);

void end_element(void *data, const char *el);

int xmlParse(GtkWidget *widget, GtkWidget *fileName);

#endif