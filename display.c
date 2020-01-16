#include <gtk/gtk.h>
#include <string.h>
#include <cairo.h>
#include "parsing.h"
#include "calculations.h"
#include "draw.h"
/*
 *  TWORZENIE INFORMACJI O DANEJ STATYSTYCE
 */
char* makeLabelName (char *type) {
   char nameBase[16];
   static char fullName[32];
   if(!strcmp(type, "date")) {
      strcpy(fullName, "Data: ");
      g_snprintf(nameBase, 17, "%d", path -> date[0].day);
      if(path -> date[0].day < 10)
         strcat(fullName, "0");
      strcat(fullName, nameBase);
      strcat(fullName, ".");
      g_snprintf(nameBase, 17, "%d", path -> date[0].month);
      if(path -> date[0].month < 10)
         strcat(fullName, "0");
      strcat(fullName, nameBase);
      strcat(fullName, ".");
      g_snprintf(nameBase, 17, "%d", path -> date[0].year);
      strcat(fullName, nameBase);
   }
   else if(!strcmp(type, "time")) {
      strcpy(fullName, "Czas: ");
      if(pathDuration() / 3600 > 0) {
         if(pathDuration() / 3600 < 10)
            strcat(fullName, "0");
         g_snprintf(nameBase, 17, "%lld", pathDuration() / 3600);
         strcat(fullName, nameBase);
         strcat(fullName, ":");
      }
      if((pathDuration() % 3600) / 60 < 10)
         strcat(fullName, "0");
      g_snprintf(nameBase, 17, "%lld", (pathDuration() % 3600) / 60);
      strcat(fullName, nameBase);
      strcat(fullName, ":");
      if(pathDuration() % 60 < 10)
         strcpy(fullName, "0");
      g_snprintf(nameBase, 17, "%lld", pathDuration() % 60);
      strcat(fullName, nameBase);
   }
   else if(!strcmp(type, "dist")) {
      strcpy(fullName, "Dlugosc trasy: ");
      g_snprintf(nameBase, 17, "%.2lf", fullDistance());
      strcat(fullName, nameBase);
      strcat(fullName, " km");
   }
   else if(!strcmp(type, "avgV")) {
      strcpy(fullName, "Srednia predkosc: ");
      g_snprintf(nameBase, 16, "%.2lf", fullDistance() / ((double)pathDuration() / 3600));
      strcat(fullName, nameBase);
      strcat(fullName, " km/h");
   }
   else if(!strcmp(type, "minH")) {
      strcpy(fullName, "Najnizszy punkt: ");
      g_snprintf(nameBase, 16, "%.2lf", minHeight());
      strcat(fullName, nameBase);
      strcat(fullName, " m");
   }
   else if(!strcmp(type, "maxH")) {
      strcpy(fullName, "Najwyzszy punkt: ");
      g_snprintf(nameBase, 16, "%.2lf", maxHeight());
      strcat(fullName, nameBase);
      strcat(fullName, " m");
   }
   else if(!strcmp(type, "difH")) {
      strcpy(fullName, "Roznica wysokosci: ");
      g_snprintf(nameBase, 16, "%.2lf", heightDif ());
      strcat(fullName, nameBase);
      strcat(fullName, " m");
   }
   return fullName;
}

/*
 *  OKNO ZE STATYSTYKAMI
 */
void statsWindow (GtkWidget *widget, GtkWidget *entry) {
   if(!pathParse(gtk_entry_get_text(GTK_ENTRY(entry)))) {
   GtkWidget *statsWindow;
   GtkWidget *mainBox;
   GtkWidget *statsBox;
   GtkWidget *drawingArea;
   GtkWidget *dateText;
   GtkWidget *timeText;
   GtkWidget *distanceText;
   GtkWidget *avgSpeedText;
   GtkWidget *minHText;
   GtkWidget *maxHText;
   GtkWidget *difHText;
   GtkWidget *buttonBox;
   GtkWidget *closeButton;
   GtkWidget *drawButton;

   statsWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(statsWindow), "Statystyki");
   gtk_window_set_default_size(GTK_WINDOW(statsWindow), 900, 400);
   gtk_container_set_border_width(GTK_CONTAINER(statsWindow), 10);
   gtk_window_set_resizable(GTK_WINDOW(statsWindow), FALSE);

   mainBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
   gtk_container_add(GTK_CONTAINER(statsWindow), mainBox);

   statsBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
   gtk_box_pack_start(GTK_BOX(mainBox), statsBox, FALSE, TRUE, 0);

   drawingArea = gtk_drawing_area_new();
   gtk_box_pack_start(GTK_BOX(mainBox), drawingArea, TRUE, TRUE, 0);
   /* DATA */
   dateText = gtk_label_new(makeLabelName("date"));
   gtk_box_pack_start(GTK_BOX(statsBox), dateText, TRUE, TRUE, 0);
   /* CZAS */
   timeText = gtk_label_new(makeLabelName("time"));
   gtk_box_pack_start(GTK_BOX(statsBox), timeText, TRUE, TRUE, 0);
   /* ŁĄCZNY DYSTANS */
   distanceText = gtk_label_new(makeLabelName("dist"));
   gtk_box_pack_start(GTK_BOX(statsBox), distanceText, TRUE, TRUE, 0);
   /* ŚREDNIA PRĘDKOŚĆ */
   avgSpeedText = gtk_label_new(makeLabelName("avgV"));
   gtk_box_pack_start(GTK_BOX(statsBox), avgSpeedText, TRUE, TRUE, 0);
   /* NAJNIŻSZY PUNKT */
   minHText = gtk_label_new(makeLabelName("minH"));
   gtk_box_pack_start(GTK_BOX(statsBox), minHText, TRUE, TRUE, 0);
   /* NAJWYŻSZY PUNKT */
   maxHText = gtk_label_new(makeLabelName("maxH"));
   gtk_box_pack_start(GTK_BOX(statsBox), maxHText, TRUE, TRUE, 0);
   /* ROZNICA WYSOKOSCI */
   difHText = gtk_label_new(makeLabelName("difH"));
   gtk_box_pack_start(GTK_BOX(statsBox), difHText, TRUE, TRUE, 0);

   buttonBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
   gtk_box_set_homogeneous(GTK_BOX(buttonBox), TRUE);
   gtk_widget_set_margin_start(buttonBox, 50);
   gtk_widget_set_margin_end(buttonBox, 50);
   gtk_box_pack_start(GTK_BOX(statsBox), buttonBox, FALSE, TRUE, 0);
   /* PRZYCISK ZAMKNIJ */
   closeButton = gtk_button_new_with_label("Zamknij");
   gtk_box_pack_start(GTK_BOX(buttonBox), closeButton, FALSE, TRUE, 0);

   drawButton = gtk_button_new_with_label("Pokaz mape");
   gtk_box_pack_start(GTK_BOX(buttonBox), drawButton, FALSE, TRUE, 0);

   g_signal_connect(G_OBJECT(drawingArea), "draw", G_CALLBACK(on_draw_event), NULL);
   g_signal_connect_swapped(drawButton, "clicked", G_CALLBACK(clicked), statsWindow);

   g_signal_connect(closeButton, "clicked", G_CALLBACK(gtk_window_close), statsWindow);

   g_signal_connect(statsWindow, "destroy", G_CALLBACK(gtk_widget_destroy), statsWindow);

   gtk_widget_show_all(statsWindow);

   pathFree();
}}
/*
 *  OKNO POMOCY
 */
void helpWindow () {
   GtkWidget *helpWindow;
   GtkWidget *mainBox;
   GtkWidget *help;
   GtkWidget *closeButton;

   helpWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(helpWindow), "Pomoc");
   gtk_window_set_default_size(GTK_WINDOW(helpWindow), 300, 180);
   gtk_container_set_border_width(GTK_CONTAINER(helpWindow), 10);

   mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
   gtk_container_add(GTK_CONTAINER(helpWindow), mainBox);
   /* TEKST POMOCY */
   help = gtk_label_new("Lorem ipsum – tekst skladajacy sie z lacinskichi quasi-lacinskich\nwyrazow, majacy korzenie w klasycznej lacinie, wzorowany na fragmencie\ntraktatu Cycerona „O granicach dobra i zla” (De finibus bonorum\net malorum) napisanego w 45 p.n.e. Tekst jest stosowany do demonstracji\nkrojow pisma (czcionek, fontow), kompozycji kolumny itp. Po raz pierwszy\nzostal uzyty przez nieznanego drukarza w XVI wieku.");
   gtk_box_pack_start(GTK_BOX(mainBox), help, TRUE, TRUE, 0);
   /* PRZYCISK ZAMKNIJ */
   closeButton = gtk_button_new_with_label("Zamknij");
   gtk_widget_set_margin_start(closeButton, 150);
   gtk_widget_set_margin_end(closeButton, 150);
   gtk_box_pack_start(GTK_BOX(mainBox), closeButton, FALSE, TRUE, 0);

   g_signal_connect(closeButton, "clicked", G_CALLBACK(gtk_window_close), helpWindow);

   g_signal_connect(helpWindow, "destroy", G_CALLBACK(gtk_widget_destroy), helpWindow);

   gtk_widget_show_all(helpWindow);
}

void setEntry (GtkWidget *widget, GtkWidget *entry) {
   gtk_editable_select_region(GTK_EDITABLE(entry), 0, gtk_entry_get_text_length(GTK_ENTRY(entry)));
   gtk_widget_grab_focus(entry);
}
/*
 *  MENU GŁÓWNE
 */
void mainMenu () {
   static GtkWidget *entry;
   GtkWidget *mainMenu;
   GtkWidget *confirmButton;
   GtkWidget *exitButton;
   GtkWidget *helpButton;
   GtkWidget *mainBox;
   GtkWidget *hBox;

   mainMenu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(mainMenu), "Testowy program");
   gtk_window_set_default_size(GTK_WINDOW(mainMenu), 400, 280);
   gtk_window_set_position(GTK_WINDOW(mainMenu), GTK_WIN_POS_CENTER);
   gtk_window_set_resizable(GTK_WINDOW(mainMenu), FALSE);

   mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
   gtk_container_add(GTK_CONTAINER(mainMenu), mainBox);
   gtk_widget_set_margin_start(mainBox, 70);
   gtk_widget_set_margin_end(mainBox, 70);
   gtk_widget_set_margin_top(mainBox, 70);
   gtk_widget_set_margin_bottom(mainBox,70);
   /* WPROWADZANIE SCIEZKI DO PLIKU */
   entry = gtk_entry_new();
   gtk_entry_set_max_length(GTK_ENTRY(entry), 50);
   gtk_entry_set_text(GTK_ENTRY(entry), "Wprowadz tekst");
   gtk_editable_select_region(GTK_EDITABLE(entry), 0, gtk_entry_get_text_length(GTK_ENTRY(entry)));
   gtk_box_pack_start(GTK_BOX(mainBox), entry, TRUE, TRUE, 0);

   hBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
   gtk_box_set_homogeneous(GTK_BOX(hBox), TRUE);
   gtk_box_pack_start(GTK_BOX(mainBox), hBox, TRUE, TRUE, 0);
   /* PRZYCISK WYJSCIE */
   exitButton = gtk_button_new_with_label("Wyjscie");
   g_signal_connect(exitButton, "clicked", G_CALLBACK(gtk_main_quit), NULL);
   gtk_box_pack_start(GTK_BOX(hBox), exitButton, TRUE, TRUE, 1);
   /* PRZYCISK POTWIERDZ */
   confirmButton = gtk_button_new_with_label("Potwierdz");
   g_signal_connect(confirmButton, "clicked", G_CALLBACK(statsWindow), (gpointer) entry);
   g_signal_connect(confirmButton, "clicked", G_CALLBACK(setEntry), (gpointer) entry);
   gtk_box_pack_start(GTK_BOX(hBox), confirmButton, TRUE, TRUE, 1);
   /* PRZYCISK POMOC */
   helpButton = gtk_button_new_with_label("Pomoc");
   g_signal_connect(helpButton, "clicked", G_CALLBACK(helpWindow), NULL);
   gtk_box_pack_end(GTK_BOX(mainBox), helpButton, TRUE, TRUE, 0);

   g_signal_connect(mainMenu, "destroy", G_CALLBACK(gtk_main_quit), NULL);

   gtk_widget_show_all(mainMenu);
}
/*
 *  INFORMACJA O NIEODNALEZIENIU DANEGO PLIKU
 */
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