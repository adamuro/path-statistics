#ifndef DRAW_H
#define DRAW_H

#ifndef MapWidth
#define MapWidth 450
#endif
#ifndef MapHeight
#define MapHeight 300
#endif

#include "common.h"

void doDrawing (cairo_t *);

void drawingAreaSetup (GtkWidget *win);

gboolean onDrawEvent (GtkWidget *widget, cairo_t *cr, gpointer user_data);

#endif