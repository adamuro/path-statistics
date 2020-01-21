#include <cairo.h>
#include <gtk/gtk.h>
#include "structures.h"
#include "parsing.h"
/*
 *  PRZYGOTOWANIE OBSZARU DO RYSOWANIA
 */
void drawingAreaSetup (GtkWidget *drawingArea) {        
   GdkScreen *Screen;
   GdkVisual *Visual;

   Screen = gdk_screen_get_default();
   Visual = gdk_screen_get_rgba_visual(Screen);

   if (Visual != NULL && gdk_screen_is_composited(Screen)) {
      gtk_widget_set_visual(drawingArea, Visual);
   }
}
/*
 *  RYSOWANIE MAPY
 */
void doDrawing (cairo_t *cr) {
   for (int i = 0 ; i < path -> pointsNum - 1 ; i++) {
      cairo_move_to(cr, path -> point[i].lat + i - 1, path -> point[i].lon + i - 1);
      cairo_line_to(cr, path -> point[i + 1].lat + i, path -> point[i + 1].lon + i);
      //printf("%lf %lf\n", path -> point[i].lat + i, path -> point[i].lon + i);
   }
   cairo_line_to(cr, 30.8943, 26.739752);
   cairo_stroke(cr);
}
/*
 *  FUNKCJA POŚREDNIA RYSOWANIA
 */
gboolean onDrawEvent (GtkWidget *widget, cairo_t *cr, gpointer user_data) {
   doDrawing(cr);
   return FALSE;
}

