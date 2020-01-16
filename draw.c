#include <cairo.h>
#include <gtk/gtk.h>

struct {
  int count;
  double coordx[100];
  double coordy[100];
} glob;

void do_drawing(cairo_t *cr) {
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width(cr, 0.5);

  for (int i = 0; i < glob.count - 1; i++ ) {
      cairo_move_to(cr, glob.coordx[i], glob.coordy[i]);
      cairo_line_to(cr, glob.coordx[i + 1], glob.coordy[i + 1]);
      printf("%lf %lf\n", glob.coordx[i], glob.coordy[i]);
  }

  glob.count = 0;
  cairo_stroke(cr);    
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  do_drawing(cr);
  return FALSE;
}


gboolean clicked (GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    for(int i = 0 ; i < 5 ; i++) {
      glob.coordx[i] = i * 30;
      glob.coordy[i] = i * 20;
      glob.count = 5;
    }
    gtk_widget_queue_draw(widget);

    return TRUE;
}