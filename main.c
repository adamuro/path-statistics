#include "common.h"

int main (int argc, char **argv) {
   gtk_init(&argc, &argv);
   
   mainMenu();

   gtk_main();

   pathFree();

 	return 0;
}