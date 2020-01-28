#include "draw.h"

void drawingAreaSetup (GtkWidget *drawingArea) {        
   GdkScreen *Screen;
   GdkVisual *Visual;

   Screen = gdk_screen_get_default();
   Visual = gdk_screen_get_rgba_visual(Screen);

   if (Visual != NULL && gdk_screen_is_composited(Screen)) {
      gtk_widget_set_visual(drawingArea, Visual);
   }
}

void doDrawing (cairo_t *drawingArea) {
   double difX;
   double difY;
   double minX;
   double minY;

   cartesianMinimums(&minX, &minY, Path -> Point, Path -> pointsNum);
   cartesianDiffs(minX, minY, &difX, &difY, Path -> Point, Path -> pointsNum);
   
   for (int i = 0 ; i < Path -> pointsNum - 1 ; i++) {
      cairo_move_to(drawingArea, (convertToCartesianX(Path -> Point[i]) - minX) * (MapWidth / difX) + 10,
         (convertToCartesianY(Path -> Point[i]) - minY) * (MapHeight / difY) + 10);
      cairo_line_to(drawingArea, (convertToCartesianX(Path -> Point[i + 1]) - minX) * (MapWidth / difX) + 10,
         (convertToCartesianY(Path -> Point[i + 1]) - minY) * (MapHeight / difY) + 10);
   }
   cairo_stroke(drawingArea);
}

gboolean onDrawEvent (GtkWidget *Widget, cairo_t *drawingArea, gpointer userData) {
   doDrawing(drawingArea);
   return TRUE;
}

