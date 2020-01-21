#include <gtk/gtk.h>
#include "display.h"
#include "parsing.h"

int main (int argc, char **argv) {
   gtk_init(&argc, &argv);
   
   mainMenu();

   gtk_main();

   pathFree();

   free(path);

  return 0;
}