#include <gtk/gtk.h>
#include "display.h"

int main (int argc, char **argv) {
   gtk_init(&argc, &argv);
   
   mainMenu();

   gtk_main();

  return 0;
}