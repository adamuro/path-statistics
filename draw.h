#ifndef DRAW_H
#define DRAW_H

#define MapWidth 500
#define MapHeight 350

#include "common.h"

void doDrawing (cairo_t *drawingArea); // Draw a map of the path in the drawing area
void drawingAreaSetup (GtkWidget *drawingArea); // Set up the drawing area
gboolean onDrawEvent (GtkWidget *Widget, cairo_t *drawingArea, gpointer userData); // Connection between draw signal and actual function

#endif