#include <gtk/gtk.h>
#include "after.h"
#include "create_account.h"
#include "sign_in.h"

static GtkWidget *login_window;
GtkWidget *fixed;
GtkWidget *entry1;
GtkWidget *entry2;
GtkWidget *button1;
GtkWidget *button2;
GtkWidget *title;
GtkWidget *subtitle;
PangoAttrList *attr_list;
PangoAttribute *attr;

gchar username[100];
const gchar *password;

static gboolean draw_rectangle(GtkWidget *widget, cairo_t *cr, gpointer data) {
    GdkRGBA color;
    gdk_rgba_parse(&color, "white");

    int width = 300;
    int height = 400;
    int x = (gtk_widget_get_allocated_width(widget) - width) / 2;
    int y = (gtk_widget_get_allocated_height(widget) - height) / 2;

    cairo_set_source_rgba(cr, color.red, color.green, color.blue, color.alpha);
    cairo_rectangle(cr, x, y, width, height);
    cairo_fill(cr);

    return FALSE;
}

void on_button1_clicked(GtkWidget *widget, gpointer data) {

    // first do login check then click button1
    struct hash_table table;
    table.size = HASH_SIZE;
    table.users = malloc(sizeof(struct user *) * table.size);
    memset(table.users, 0, sizeof(struct user *) * table.size);

    // load users from file
    load_users(&table, "users.dat");

    // create some sample users
    int choice, Login_successful = 0;
        
    // authenticate user
    // username = gtk_entry_get_text(GTK_ENTRY(entry1));
    strcpy(username, gtk_entry_get_text(GTK_ENTRY(entry1)));
    password = gtk_entry_get_text(GTK_ENTRY(entry2));
    if (find_user(&table, username, password)) {
        // g_print("Login successful!\n");
        Login_successful = 1;
    } else {
        // g_print("Login failed. Invalid username or password.\n");
    }

    // save users to file before exiting
    save_users(&table, "users.dat");

    if(Login_successful) {
        gtk_widget_destroy(login_window);
        create_after_window(username);
    }
}

int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);

    login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(login_window), 600, 600);
    gtk_window_set_position(GTK_WINDOW(login_window), GTK_WIN_POS_CENTER);

    fixed = gtk_fixed_new();

    entry1 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Username");
    entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);

    button1 = gtk_button_new_with_label("LOG IN");
    gtk_widget_set_size_request(button1, 165, 20);

    button2 = gtk_button_new_with_label("SIGN UP");
    gtk_widget_set_size_request(button2, 165, 20);

    title = gtk_label_new("PLAYER DATA");
    attr_list = pango_attr_list_new();
    attr = pango_attr_foreground_new(65535, 32768, 0);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(title), attr_list);
    attr = pango_attr_weight_new(PANGO_WEIGHT_BOLD);
    pango_attr_list_insert(attr_list, attr);
    attr = pango_attr_size_new(24 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(title), attr_list);
    pango_attr_list_unref(attr_list);

    subtitle = gtk_label_new("LOG IN");
    attr_list = pango_attr_list_new();
    attr = pango_attr_weight_new(PANGO_WEIGHT_BOLD);
    pango_attr_list_insert(attr_list, attr);
    attr = pango_attr_size_new(18 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(subtitle), attr_list);
    pango_attr_list_unref(attr_list);

    gtk_fixed_put(GTK_FIXED(fixed), title, 210, 150);
    gtk_fixed_put(GTK_FIXED(fixed), subtitle, 260, 200);
    gtk_fixed_put(GTK_FIXED(fixed), entry1, 210, 250);
    gtk_fixed_put(GTK_FIXED(fixed), entry2, 210, 300);
    gtk_fixed_put(GTK_FIXED(fixed), button2, 210, 350);
    gtk_fixed_put(GTK_FIXED(fixed), button1, 210, 400);

    gtk_widget_show(title);
    gtk_widget_show(subtitle);

    g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), NULL);
    // on_button1_clicked(button1, NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button2_clicked), NULL);
    g_signal_connect(login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_set_app_paintable(login_window, TRUE);
    g_signal_connect(login_window, "draw", G_CALLBACK(draw_rectangle), NULL);

    gtk_container_add(GTK_CONTAINER(login_window), fixed);
    gtk_widget_show_all(login_window);

    gtk_main();

    return 0;
}