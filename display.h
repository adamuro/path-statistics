#ifndef DISPLAY_H
#define DISPLAY_H

#include "common.h"

char* makeLabelName (char *type); // Create a string that contains information about a certain statistic
void statsWindow (char *fileName); // Open a window with the path statistics
void fileSelection (); // Open a file selection dialog
void mainMenu ();
void helpWindow ();
void fileError (char *errorCode); // Message about error during file opening
void setEntry (GtkWidget *Entry); // Set focus on the entry field

#endif