#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

#include <gtk/gtk.h>
#include "after.h"

extern GtkWidget *error_label;

gboolean check_username_exists();
gboolean check_passwords_match();
void create_account(GtkButton *button, gpointer user_data);
void create_create_account_window();
void on_button2_clicked(GtkWidget *widget, gpointer data);
#endif
