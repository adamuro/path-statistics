#include "draw.h"
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
   double difX = cartesianDifX(path -> point, path -> pointsNum);
   double difY = cartesianDifY(path -> point, path -> pointsNum);
   double minX = minCartesianX(path -> point, path -> pointsNum);
   double minY = minCartesianY(path -> point, path -> pointsNum);
   
   for (int i = 0 ; i < path -> pointsNum - 1 ; i++) {
      cairo_move_to(cr, (convertToCartesianX(path -> point[i]) - minX) * (MapWidth / difX),
         (convertToCartesianY(path -> point[i]) - minY) * (MapHeight / difY));
      cairo_line_to(cr, (convertToCartesianX(path -> point[i + 1]) - minX) * (MapWidth / difX),
         (convertToCartesianY(path -> point[i + 1]) - minY) * (MapHeight / difY));
      //printf("%lf %lf\n", convertToCartesianX(path -> point[i]), convertToCartesianY(path -> point[i]));
   }

   cairo_stroke(cr);
}
/*
 *  FUNKCJA POŚREDNIA RYSOWANIA
 */
gboolean onDrawEvent (GtkWidget *widget, cairo_t *cr, gpointer user_data) {
   doDrawing(cr);
   return FALSE;
}

