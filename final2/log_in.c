#include <gtk/gtk.h>
#include "after.h"

void log_in() {
    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *button1;
    GtkWidget *title;
    GtkWidget *subtitle;
    PangoAttrList *attr_list;
    PangoAttribute *attr;
    gchar *username;
    gchar *password;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    fixed = gtk_fixed_new();

    entry1 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Username");
    entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);

    button1 = gtk_button_new_with_label("SIGN IN");
    gtk_widget_set_size_request(button1, 165, 20);

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

    subtitle = gtk_label_new("SIGN IN");
    attr_list = pango_attr_list_new();
    attr = pango_attr_weight_new(PANGO_WEIGHT_BOLD);
    pango_attr_list_insert(attr_list, attr);
    attr = pango_attr_size_new(18 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(subtitle), attr_list);
    pango_attr_list_unref(attr_list);

    gtk_fixed_put(GTK_FIXED(fixed), button1, 100, 270);
    gtk_fixed_put(GTK_FIXED(fixed), entry1, 100, 150);
    gtk_fixed_put(GTK_FIXED(fixed), entry2, 100, 200);
    gtk_fixed_put(GTK_FIXED(fixed), title, 100, 50);
    gtk_fixed_put(GTK_FIXED(fixed), subtitle, 125, 100);

    gtk_widget_show(title);
    gtk_widget_show(subtitle);

    // first do login check then click button1
    // g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), NULL);
    struct hash_table table;
    table.size = HASH_SIZE;
    table.users = malloc(sizeof(struct user *) * table.size);
    memset(table.users, 0, sizeof(struct user *) * table.size);

    // load users from file
    load_users(&table, "users.dat");

    // create some sample users
    int choice, Login_successful = 0;
    while (Login_successful == 0) {
        
        // authenticate user
        username = gtk_entry_get_text(entry1);
        password = gtk_entry_get_text(entry2);
        if (find_user(&table, username, password)) {
            // printf("Login successful!\n\n");
            Login_successful = 1;
        } else {
            // printf("Login failed. Invalid username or password.\n\n");
            // show unsuccesful
        }
        

        /* original code
        if (choice == 1) {
            create_user(&table);
        } else {
            // authenticate user
            if (find_user(&table)) {
                // printf("Login successful!\n\n");
                Login_successful = 1;
            } else {
                // printf("Login failed. Invalid username or password.\n\n");
            }
        }
        */
    }

    // save users to file before exiting
    save_users(&table, "users.dat");

    // can call on_button1_clicked because if loop broke, login successful
    on_button1_clicked(username);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show_all(window);

    gtk_main();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    log_in();

    return 0;
}