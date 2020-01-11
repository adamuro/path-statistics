#include <gtk/gtk.h>
#include "loading.h"
#include "calculations.h"

void statsWindow (GtkWidget *widget, GtkWidget *entry) {
   if(!xmlParse(gtk_entry_get_text(GTK_ENTRY(entry)))) {
   GtkWidget *statsWindow;
   GtkWidget *mainBox;
   GtkWidget *lengthBox;
   GtkWidget *lengthText;
   GtkWidget *length;
   GtkWidget *closeButton;

   char msg[32];
   g_snprintf(msg, 32, "%lf", fullDistance());

   statsWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(statsWindow), "Statystyki");
   gtk_window_set_default_size(GTK_WINDOW(statsWindow), 400, 280);
   gtk_container_set_border_width(GTK_CONTAINER(statsWindow), 10);
   gtk_window_set_resizable(GTK_WINDOW(statsWindow), FALSE);

   mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
   gtk_container_add(GTK_CONTAINER(statsWindow), mainBox);

   lengthBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
   gtk_box_pack_start(GTK_BOX(mainBox), lengthBox, TRUE, TRUE, 0);

   lengthText = gtk_label_new("Dlugosc trasy:");
   gtk_box_pack_start(GTK_BOX(lengthBox), lengthText, TRUE, TRUE, 0);

   length = gtk_label_new(msg);
   gtk_box_pack_start(GTK_BOX(lengthBox), length, TRUE, TRUE, 0);

   closeButton = gtk_button_new_with_label("Zamknij");
   gtk_widget_set_margin_start(closeButton, 150);
   gtk_widget_set_margin_end(closeButton, 150);
   gtk_box_pack_start(GTK_BOX(mainBox), closeButton, FALSE, TRUE, 0);

   g_signal_connect(closeButton, "clicked", G_CALLBACK(gtk_window_close), statsWindow);

   g_signal_connect(statsWindow, "destroy", G_CALLBACK(gtk_widget_destroy), statsWindow);

   gtk_widget_show_all(statsWindow);
}}


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

   help = gtk_label_new("Lorem ipsum – tekst skladajacy sie z lacinskichi quasi-lacinskich\nwyrazow, majacy korzenie w klasycznej lacinie, wzorowany na fragmencie\ntraktatu Cycerona „O granicach dobra i zla” (De finibus bonorum\net malorum) napisanego w 45 p.n.e. Tekst jest stosowany do demonstracji\nkrojow pisma (czcionek, fontow), kompozycji kolumny itp. Po raz pierwszy\nzostal uzyty przez nieznanego drukarza w XVI wieku.");
   gtk_box_pack_start(GTK_BOX(mainBox), help, TRUE, TRUE, 0);

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
}

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

   entry = gtk_entry_new();
   gtk_entry_set_max_length(GTK_ENTRY(entry), 50);
   gtk_entry_set_text(GTK_ENTRY(entry), "Wprowadz tekst");
   gtk_editable_select_region(GTK_EDITABLE(entry), 0, gtk_entry_get_text_length(GTK_ENTRY(entry)));
   gtk_box_pack_start(GTK_BOX(mainBox), entry, TRUE, TRUE, 0);

   hBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
   gtk_box_set_homogeneous(GTK_BOX(hBox), TRUE);
   gtk_box_pack_start(GTK_BOX(mainBox), hBox, TRUE, TRUE, 0);

   exitButton = gtk_button_new_with_label("Wyjscie");
   g_signal_connect(exitButton, "clicked", G_CALLBACK(gtk_main_quit), NULL);
   gtk_box_pack_start(GTK_BOX(hBox), exitButton, TRUE, TRUE, 1);

   confirmButton = gtk_button_new_with_label("Potwierdz");
   g_signal_connect(confirmButton, "clicked", G_CALLBACK(statsWindow), (gpointer) entry);
   g_signal_connect(confirmButton, "clicked", G_CALLBACK(setEntry), (gpointer) entry);
   gtk_box_pack_start(GTK_BOX(hBox), confirmButton, TRUE, TRUE, 1);

   helpButton = gtk_button_new_with_label("Pomoc");
   g_signal_connect(helpButton, "clicked", G_CALLBACK(helpWindow), NULL);
   gtk_box_pack_end(GTK_BOX(mainBox), helpButton, TRUE, TRUE, 0);

   g_signal_connect(mainMenu, "destroy", G_CALLBACK(gtk_main_quit), NULL);

   gtk_widget_show_all(mainMenu);
}

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