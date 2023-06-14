#include <gtk/gtk.h>
#include "create_account.h"
#include "sign_in.h"

GtkWidget *username_entry;
GtkWidget *password_entry;
GtkWidget *confirm_entry;

GtkWidget *error_label;

static gboolean draw_rectangle(GtkWidget *widget, cairo_t *cr, gpointer data) {
    GdkRGBA color;
    gdk_rgba_parse(&color, "white");

    int width = 300;
    int height = 450;
    int x = (gtk_widget_get_allocated_width(widget) - width) / 2;
    int y = (gtk_widget_get_allocated_height(widget) - height) / 2;

    cairo_set_source_rgba(cr, color.red, color.green, color.blue, color.alpha);
    cairo_rectangle(cr, x, y, width, height);
    cairo_fill(cr);

    return FALSE;
}

void create_account(GtkButton *button, gpointer data)
{
    struct hash_table table;
    table.size = HASH_SIZE;
    table.users = malloc(sizeof(struct user *) * table.size);
    memset(table.users, 0, sizeof(struct user *) * table.size);

    // load users from file
    load_users(&table, "users.dat");
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));
    const gchar *password2 = gtk_entry_get_text(GTK_ENTRY(confirm_entry));

    if (strcmp(password, password2) == 0) {
        struct user *new_user = malloc(sizeof(struct user));
        strcpy(new_user->username, username);
        strcpy(new_user->password, password);
        insert_new_user(&table, new_user);
        g_print("Sign Up successful!\n");

        save_users(&table, "users.dat");
        
        gtk_widget_destroy(data);
    }
    else {
        gchar *error_message = g_strdup("-Password not match-");

        gtk_label_set_text(GTK_LABEL(error_label), error_message);

        g_free(error_message);
    }

}

void cancel_clicked(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy(data);
}

void create_create_account_window()
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *fixed2;
    gtk_window_set_title(GTK_WINDOW(window), "SIGN UP");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 600, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    error_label = gtk_label_new(NULL);

    fixed2 = gtk_fixed_new();
    
    GtkWidget *title = gtk_label_new("PLAYER DATA");
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr = pango_attr_foreground_new(65535, 32768, 0);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(title), attr_list);
    attr = pango_attr_weight_new(PANGO_WEIGHT_BOLD);
    pango_attr_list_insert(attr_list, attr);
    attr = pango_attr_size_new(24 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(title), attr_list);
    pango_attr_list_unref(attr_list);

    // 創建副標題標籤
    GtkWidget *subtitle = gtk_label_new("SIGN UP");
    attr_list = pango_attr_list_new();
    attr = pango_attr_weight_new(PANGO_WEIGHT_BOLD);
    pango_attr_list_insert(attr_list, attr);
    attr = pango_attr_size_new(18 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(subtitle), attr_list);

    username_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");

    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");

    confirm_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(confirm_entry), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(confirm_entry), "Confirm Password");

    GtkWidget *button_cancel = gtk_button_new_with_label("Cancel");
    gtk_widget_set_size_request(button_cancel, 165, 20);
    g_signal_connect(button_cancel, "clicked", G_CALLBACK(cancel_clicked), window);

    GtkWidget *button_sign = gtk_button_new_with_label("Sign Up");
    gtk_widget_set_size_request(button_sign, 165, 20);
    g_signal_connect(button_sign, "clicked", G_CALLBACK(create_account), window);

    gtk_fixed_put(GTK_FIXED(fixed2), title, 210, 140);
    gtk_fixed_put(GTK_FIXED(fixed2), subtitle, 250, 190);
    gtk_fixed_put(GTK_FIXED(fixed2), error_label, 220, 220);
    gtk_fixed_put(GTK_FIXED(fixed2), username_entry, 210, 240);
    gtk_fixed_put(GTK_FIXED(fixed2), password_entry, 210, 290);
    gtk_fixed_put(GTK_FIXED(fixed2), confirm_entry, 210, 340);
    gtk_fixed_put(GTK_FIXED(fixed2), button_cancel, 210, 390);
    gtk_fixed_put(GTK_FIXED(fixed2), button_sign, 210, 440);

    gtk_widget_show(title);
    gtk_widget_show(subtitle);

    gtk_widget_set_app_paintable(window, TRUE);
    g_signal_connect(window, "draw", G_CALLBACK(draw_rectangle), NULL);

    gtk_container_add(GTK_CONTAINER(window), fixed2);
    gtk_widget_show_all(window);

    gtk_main();
};

void on_button2_clicked(GtkWidget *widget, gpointer data)
{
    create_create_account_window();
};