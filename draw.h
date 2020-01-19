#ifndef DRAW_H
#define DRAW_H

void doDrawing (cairo_t *);

void drawingAreaSetup (GtkWidget *win);

gboolean onDrawEvent (GtkWidget *widget, cairo_t *cr, gpointer user_data);

#endif