#include "display.h"

void fileOpenError () {
   GtkWidget *errorWindow;
   GtkWidget *mainBox;
   GtkWidget *errorMessage;
   GtkWidget *okButton;

   errorWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(errorWindow), "Blad!");
   gtk_window_set_default_size(GTK_WINDOW(errorWindow), 100, 60);
   gtk_window_set_position(GTK_WINDOW(errorWindow), GTK_WIN_POS_CENTER);
   gtk_window_set_resizable(GTK_WINDOW(errorWindow), FALSE);
   gtk_container_set_border_width(GTK_CONTAINER(errorWindow), 10);

   mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
   gtk_container_add(GTK_CONTAINER(errorWindow), mainBox);

   errorMessage = gtk_label_new("Nie znaleziono pliku!");
   gtk_box_pack_start(GTK_BOX(mainBox), errorMessage, TRUE, TRUE, 0);

   okButton = gtk_button_new_with_label("Ok");
   gtk_widget_set_margin_start(okButton, 30);
   gtk_widget_set_margin_end(okButton, 30);
   gtk_box_pack_start(GTK_BOX(mainBox), okButton, TRUE, TRUE, 0);

   g_signal_connect(okButton, "clicked", G_CALLBACK(gtk_window_close), errorWindow);

   g_signal_connect(errorWindow, "destroy", G_CALLBACK(gtk_widget_destroy), errorWindow);

   gtk_widget_show_all(errorWindow);
}

char* makeLabelName (char *type) {
   char namePart[16];
   static char fullName[32];
   if(!strcmp(type, "date")) {
      strcpy(fullName, "Data: ");
      g_snprintf(namePart, 16, "%d", Path -> Date[0].day);
      if(Path -> Date[0].day < 10)
         strcat(fullName, "0");
      strcat(fullName, namePart);
      strcat(fullName, ".");
      g_snprintf(namePart, 16, "%d", Path -> Date[0].month);
      if(Path -> Date[0].month < 10)
         strcat(fullName, "0");
      strcat(fullName, namePart);
      strcat(fullName, ".");
      g_snprintf(namePart, 16, "%d", Path -> Date[0].year);
      strcat(fullName, namePart);
   }
   else if(!strcmp(type, "time")) {
      strcpy(fullName, "Czas: ");
      if(PathDuration() / 3600 > 0) {
         if(PathDuration() / 3600 < 10)
            strcat(fullName, "0");
         g_snprintf(namePart, 16, "%lld", PathDuration() / 3600);
         strcat(fullName, namePart);
         strcat(fullName, ":");
      }
      if((PathDuration() % 3600) / 60 < 10)
         strcat(fullName, "0");
      g_snprintf(namePart, 16, "%lld", (PathDuration() % 3600) / 60);
      strcat(fullName, namePart);
      strcat(fullName, ":");
      if(PathDuration() % 60 < 10)
         strcat(fullName, "0");
      g_snprintf(namePart, 16, "%lld", PathDuration() % 60);
      strcat(fullName, namePart);
   }
   else if(!strcmp(type, "dist")) {
      strcpy(fullName, "Dlugosc trasy: ");
      g_snprintf(namePart, 16, "%.2lf", fullDistance());
      strcat(fullName, namePart);
      strcat(fullName, " km");
   }
   else if(!strcmp(type, "avgV")) {
      strcpy(fullName, "Srednia predkosc: ");
      g_snprintf(namePart, 16, "%.2lf", averageSpeed());
      strcat(fullName, namePart);
      strcat(fullName, " km/h");
   }
   else if(!strcmp(type, "maxV")) {
      strcpy(fullName, "Najwyzsza predkosc: ");
      g_snprintf(namePart, 16, "%.2lf", maxSpeed());
      strcat(fullName, namePart);
      strcat(fullName, " km/h");
   }
   else if(!strcmp(type, "minV")) {
      strcpy(fullName, "Najnizsza predkosc: ");
      g_snprintf(namePart, 16, "%.2lf", minSpeed());
      strcat(fullName, namePart);
      strcat(fullName, " km/h");
   }
   else if(!strcmp(type, "avgT")) {
      strcpy(fullName, "Srednie tempo: ");
      g_snprintf(namePart, 16, "%d", (int)averageTempo());
      strcat(fullName, namePart);
      strcat(fullName, ":");
      double decimalPart, seconds;                  // 
      decimalPart = modf(averageTempo(), &seconds); // Calculate number of seconds
      seconds = (int)(decimalPart * 60);            //
      if(seconds < 10)
         strcat(fullName, "0");
      g_snprintf(namePart, 16, "%.0lf", seconds);
      strcat(fullName, namePart);
      strcat(fullName, " min/km");
   }
   else if(!strcmp(type, "maxT")) {
      strcpy(fullName, "Najwyzsze tempo: ");
      g_snprintf(namePart, 16, "%d", (int)maxTempo());
      strcat(fullName, namePart);
      strcat(fullName, ":");
      double decimalPart, seconds;
      decimalPart = modf(maxTempo(), &seconds);
      seconds = (int)(decimalPart * 60);
      if(seconds < 10)
         strcat(fullName, "0");
      g_snprintf(namePart, 16, "%.0lf", seconds);
      strcat(fullName, namePart);
      strcat(fullName, " min/km");
   }
   else if(!strcmp(type, "minT")) {
      strcpy(fullName, "Najnizsze tempo: ");
      g_snprintf(namePart, 16, "%d", (int)minTempo());
      strcat(fullName, namePart);
      strcat(fullName, ":");
      double decimalPart, seconds;
      decimalPart = modf(minTempo(), &seconds);
      seconds = (int)(decimalPart * 60);
      if(seconds < 10)
         strcat(fullName, "0");
      g_snprintf(namePart, 16, "%.0lf", seconds);
      strcat(fullName, namePart);
      strcat(fullName, " min/km");
   }
   else if(!strcmp(type, "minH")) {
      strcpy(fullName, "Najnizszy punkt: ");
      g_snprintf(namePart, 16, "%.2lf", minHeight());
      strcat(fullName, namePart);
      strcat(fullName, " m");
   }
   else if(!strcmp(type, "maxH")) {
      strcpy(fullName, "Najwyzszy punkt: ");
      g_snprintf(namePart, 16, "%.2lf", maxHeight());
      strcat(fullName, namePart);
      strcat(fullName, " m");
   }
   else if(!strcmp(type, "difH")) {
      strcpy(fullName, "Roznica wysokosci: ");
      g_snprintf(namePart, 16, "%.2lf", heightDif ());
      strcat(fullName, namePart);
      strcat(fullName, " m");
   }
   return fullName;
}

void statsWindow (char *fileName) {
   if(PathParse(fileName)) {
      GtkWidget *statsWindow;
      GtkWidget *mainBox;
      GtkWidget *Separator;
      GtkWidget *statsBox;
      GtkWidget *drawingArea;
      GtkWidget *dateText;
      GtkWidget *timeText;
      GtkWidget *distanceText;
      GtkWidget *avgSpeedText;
      GtkWidget *maxSpeedText;
      GtkWidget *minSpeedText;
      GtkWidget *avgTempoText;
      GtkWidget *maxTempoText;
      GtkWidget *minTempoText;
      GtkWidget *minHText;
      GtkWidget *maxHText;
      GtkWidget *difHText;
      GtkWidget *closeButton;

      statsWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
      gtk_window_set_position(GTK_WINDOW(statsWindow), GTK_WIN_POS_CENTER);
      gtk_window_set_title(GTK_WINDOW(statsWindow), "Statystyki");
      gtk_window_set_default_size(GTK_WINDOW(statsWindow), 800, 400);
      gtk_container_set_border_width(GTK_CONTAINER(statsWindow), 10);
      gtk_window_set_resizable(GTK_WINDOW(statsWindow), FALSE);

      mainBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
      gtk_container_add(GTK_CONTAINER(statsWindow), mainBox);

      statsBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
      gtk_box_pack_start(GTK_BOX(mainBox), statsBox, FALSE, TRUE, 0);

      Separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
      gtk_box_pack_start(GTK_BOX(mainBox), Separator, FALSE, TRUE, 0);

      drawingArea = gtk_drawing_area_new();
      gtk_box_pack_start(GTK_BOX(mainBox), drawingArea, TRUE, TRUE, 0);
      /* DATE */
      dateText = gtk_label_new(makeLabelName("date"));
      gtk_box_pack_start(GTK_BOX(statsBox), dateText, TRUE, TRUE, 0);
      /* PATH DURATION */
      timeText = gtk_label_new(makeLabelName("time"));
      gtk_box_pack_start(GTK_BOX(statsBox), timeText, TRUE, TRUE, 0);
      /* FULL DISTANCE */
      distanceText = gtk_label_new(makeLabelName("dist"));
      gtk_box_pack_start(GTK_BOX(statsBox), distanceText, TRUE, TRUE, 0);
      /* AVERAGE SPEED */
      avgSpeedText = gtk_label_new(makeLabelName("avgV"));
      gtk_box_pack_start(GTK_BOX(statsBox), avgSpeedText, TRUE, TRUE, 0);
      /* HIGHEST SPEED */
      maxSpeedText = gtk_label_new(makeLabelName("maxV"));
      gtk_box_pack_start(GTK_BOX(statsBox), maxSpeedText, TRUE, TRUE, 0);
      /* LOWEST SPEED */
      minSpeedText = gtk_label_new(makeLabelName("minV"));
      gtk_box_pack_start(GTK_BOX(statsBox), minSpeedText, TRUE, TRUE, 0);
      /* AVERAGE TEMPO */
      avgTempoText = gtk_label_new(makeLabelName("avgT"));
      gtk_box_pack_start(GTK_BOX(statsBox), avgTempoText, TRUE, TRUE, 0);
      /* HIGHEST TEMPO */
      maxTempoText = gtk_label_new(makeLabelName("maxT"));
      gtk_box_pack_start(GTK_BOX(statsBox), maxTempoText, TRUE, TRUE, 0);
      /* LOWEST TEMPO */
      minTempoText = gtk_label_new(makeLabelName("minT"));
      gtk_box_pack_start(GTK_BOX(statsBox), minTempoText, TRUE, TRUE, 0);
      /* LOWEST LOCATED POINT */
      minHText = gtk_label_new(makeLabelName("minH"));
      gtk_box_pack_start(GTK_BOX(statsBox), minHText, TRUE, TRUE, 0);
      /* HIGHEST LOCATED POINT */
      maxHText = gtk_label_new(makeLabelName("maxH"));
      gtk_box_pack_start(GTK_BOX(statsBox), maxHText, TRUE, TRUE, 0);
      /* HEIGHT DIFFERENCE */
      difHText = gtk_label_new(makeLabelName("difH"));
      gtk_box_pack_start(GTK_BOX(statsBox), difHText, TRUE, TRUE, 0);

      closeButton = gtk_button_new_with_label("Zamknij");
      gtk_widget_set_margin_start(closeButton, 30);
      gtk_widget_set_margin_end(closeButton, 30);
      gtk_box_pack_start(GTK_BOX(statsBox), closeButton, TRUE, TRUE, 0);

      drawingAreaSetup(drawingArea);
      g_signal_connect(G_OBJECT(drawingArea), "draw", G_CALLBACK(onDrawEvent), NULL); 

      g_signal_connect(closeButton, "clicked", G_CALLBACK(gtk_window_close), statsWindow);

      g_signal_connect(statsWindow, "destroy", G_CALLBACK(gtk_widget_destroy), statsWindow);

      gtk_widget_show(statsWindow);

      gtk_widget_show_all(statsWindow);
   }
   else
      fileOpenError();
}
/*
 *  OKNO POMOCY
 */
void helpWindow () {
   GtkWidget *helpWindow;
   GtkWidget *mainBox;
   GtkWidget *Help;
   GtkWidget *closeButton;

   helpWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_position(GTK_WINDOW(helpWindow), GTK_WIN_POS_CENTER);
   gtk_window_set_title(GTK_WINDOW(helpWindow), "Pomoc");
   gtk_window_set_default_size(GTK_WINDOW(helpWindow), 400, 280);
   gtk_container_set_border_width(GTK_CONTAINER(helpWindow), 10);

   mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
   gtk_container_add(GTK_CONTAINER(helpWindow), mainBox);
   /* HELP TEXT */
   Help = gtk_label_new("POMOC");
   gtk_box_pack_start(GTK_BOX(mainBox), Help, TRUE, TRUE, 0);

   closeButton = gtk_button_new_with_label("Zamknij");
   gtk_widget_set_margin_start(closeButton, 150);
   gtk_widget_set_margin_end(closeButton, 150);
   gtk_box_pack_start(GTK_BOX(mainBox), closeButton, FALSE, TRUE, 0);

   g_signal_connect(closeButton, "clicked", G_CALLBACK(gtk_window_close), helpWindow);

   g_signal_connect(helpWindow, "destroy", G_CALLBACK(gtk_widget_destroy), helpWindow);

   gtk_widget_show_all(helpWindow);
}

void setEntry (GtkWidget *Widget, GtkWidget *Entry) {
   gtk_editable_select_region(GTK_EDITABLE(Entry), 0, gtk_entry_get_text_length(GTK_ENTRY(Entry)));
   gtk_widget_grab_focus(Entry);
}

void fileSelection () {
   GtkWidget *fileSelectionDialog;

   fileSelectionDialog = gtk_file_chooser_dialog_new("Wybierz plik", NULL, 
      GTK_FILE_CHOOSER_ACTION_OPEN, "Wybierz", GTK_RESPONSE_OK, 
      "Anuluj", GTK_RESPONSE_CANCEL, NULL);

   gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(fileSelectionDialog), g_get_home_dir());
   /* IF A FILE IS SELECTED, READ ITS NAME */
   gint Respnse = gtk_dialog_run(GTK_DIALOG(fileSelectionDialog));
   if(Respnse == GTK_RESPONSE_OK)
      statsWindow((gpointer) gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fileSelectionDialog)));

   gtk_widget_show_all(fileSelectionDialog);

   gtk_widget_destroy(fileSelectionDialog);
}

/*
 *  MENU GŁÓWNE
 */
void mainMenu () {
   GtkWidget *mainMenu;
   GtkWidget *mainBox;
   GtkWidget *fileSelectionBox;
   GtkWidget *Entry;
   GtkWidget *browseButton;
   GtkWidget *buttonBox;
   GtkWidget *confirmButton;
   GtkWidget *exitButton;
   GtkWidget *helpButton;

   mainMenu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(mainMenu), "Statystyki trasy");
   gtk_window_set_default_size(GTK_WINDOW(mainMenu), 400, 280);
   gtk_window_set_position(GTK_WINDOW(mainMenu), GTK_WIN_POS_CENTER);
   gtk_window_set_resizable(GTK_WINDOW(mainMenu), FALSE);

   mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
   gtk_container_add(GTK_CONTAINER(mainMenu), mainBox);
   gtk_widget_set_margin_start(mainBox, 70);
   gtk_widget_set_margin_end(mainBox, 70);
   gtk_widget_set_margin_top(mainBox, 70);
   gtk_widget_set_margin_bottom(mainBox,70);

   fileSelectionBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
   gtk_box_pack_start(GTK_BOX(mainBox), fileSelectionBox, TRUE, TRUE, 0);
   /* ENTRY FIELD FOR A PATH TO THE FILE */
   Entry = gtk_entry_new();
   gtk_entry_set_max_length(GTK_ENTRY(Entry), 50);
   gtk_entry_set_text(GTK_ENTRY(Entry), "Wprowadz tekst");
   gtk_editable_select_region(GTK_EDITABLE(Entry), 0, gtk_entry_get_text_length(GTK_ENTRY(Entry)));
   g_signal_connect_swapped(Entry, "activate", G_CALLBACK(statsWindow), (gpointer) gtk_entry_get_text(GTK_ENTRY(Entry)));
   g_signal_connect(Entry, "activate", G_CALLBACK(setEntry), (gpointer) Entry);
   gtk_box_pack_start(GTK_BOX(fileSelectionBox), Entry, TRUE, TRUE, 0);
   /* OPEN FILE SELECTION DIALOG */
   browseButton = gtk_button_new_with_label("...");
   g_signal_connect(browseButton, "clicked", G_CALLBACK(fileSelection), NULL);
   gtk_box_pack_start(GTK_BOX(fileSelectionBox), browseButton, TRUE, TRUE, 0);

   buttonBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
   gtk_box_set_homogeneous(GTK_BOX(buttonBox), TRUE);
   gtk_box_pack_start(GTK_BOX(mainBox), buttonBox, TRUE, TRUE, 0);

   exitButton = gtk_button_new_with_label("Wyjscie");
   g_signal_connect(exitButton, "clicked", G_CALLBACK(gtk_main_quit), NULL);
   gtk_box_pack_start(GTK_BOX(buttonBox), exitButton, TRUE, TRUE, 1);

   confirmButton = gtk_button_new_with_label("Potwierdz");
   g_signal_connect_swapped(confirmButton, "clicked", G_CALLBACK(statsWindow), (gpointer) gtk_entry_get_text(GTK_ENTRY(Entry)));
   g_signal_connect(confirmButton, "clicked", G_CALLBACK(setEntry), (gpointer) Entry);
   gtk_box_pack_start(GTK_BOX(buttonBox), confirmButton, TRUE, TRUE, 1);

   helpButton = gtk_button_new_with_label("Pomoc");
   g_signal_connect(helpButton, "clicked", G_CALLBACK(helpWindow), NULL);
   gtk_box_pack_end(GTK_BOX(mainBox), helpButton, TRUE, TRUE, 0);

   g_signal_connect(mainMenu, "destroy", G_CALLBACK(gtk_main_quit), NULL);

   gtk_widget_show_all(mainMenu);
}