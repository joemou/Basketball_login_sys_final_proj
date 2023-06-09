#ifndef AFTER_H
#define AFTER_H

#include <gtk/gtk.h>

enum {
    LIST_TEAM, LIST_NAME, LIST_GP, LIST_FPG, LIST_PPG, LIST_SPG, LIST_TPP, N_COLUMNS
};

void double_click_row(GtkTreeView *list, GtkTreePath *path, GtkTreeViewColumn *column, gpointer selection);

void on_ok_clicked(GtkWidget *button, gpointer data);

void on_cancel_clicked(GtkWidget *button, gpointer data);

GtkWidget *create_addwin();

void append_item(GtkWidget *widget, gpointer data);

void remove_item(GtkWidget *widget, gpointer selection);

void edit_item(GtkWidget *widget, gpointer selection);

void column_clicked(GtkTreeViewColumn *column, gpointer data);

void init_list(GtkWidget *list);

int on_search_activate(GtkEntry *entry, gpointer data);

void create_after_window(const gchar *username);

// void on_button1_clicked(GtkWidget *widget, gpointer data);

#endif
