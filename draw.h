#ifndef DRAW_H
#define DRAW_H

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);

void do_drawing(cairo_t *cr);

gboolean clicked (GtkWidget *widget, GdkEventButton *event, gpointer user_data);

#endif
