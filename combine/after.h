#ifndef AFTER_H
#define AFTER_H

#include <gtk/gtk.h>

enum {
    LIST_NAME, LIST_GP, LIST_MPG, LIST_PPG, LIST_TP, LIST_FGM, LIST_FG, LIST_PM, LIST_TO, LIST_PF, N_COLUMNS
};

// extern GtkWidget *list, *add_win, *entry_name, *entry_gp, *entry_mpg, *entry_ppg, *entry_tp, *entry_fgm, *entry_fg, *entry_pm, *entry_to, *entry_pf, *window;
// extern GtkTreeSelection *selection;

void double_click_row(GtkTreeView *list, GtkTreePath *path, GtkTreeViewColumn *column, gpointer selection);

void on_ok_clicked(GtkWidget *button, gpointer data);

void on_cancel_clicked(GtkWidget *button, gpointer data);

GtkWidget *create_addwin();

void append_item(GtkWidget *widget, gpointer data);

void remove_item(GtkWidget *widget, gpointer selection);

void edit_item(GtkWidget *widget, gpointer selection);

void column_clicked(GtkTreeViewColumn *column, gpointer data);

void init_list(GtkWidget *list);

void on_search_activate(GtkEntry *entry, gpointer data);

void create_after_window();

void on_button1_clicked(GtkWidget *widget, gpointer data);

#endif
