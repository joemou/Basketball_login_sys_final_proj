#include <gtk/gtk.h>
#include "after.h"

GtkWidget *error_label;

gboolean check_username_exists(){
    return 0;
};

gboolean check_passwords_match(){
    return 0;
};

void create_account(GtkButton *button, gpointer user_data) {
    gboolean passwords_match = check_passwords_match();
    gboolean username_exists = check_username_exists();

    if (!passwords_match || username_exists) {
        gchar *error_message = NULL;

        error_message = g_strdup("-error-");

        gtk_label_set_text(GTK_LABEL(error_label), error_message);

        g_free(error_message);
        return;
    }
}

void on_cancel_clicked2(GtkWidget *widget, gpointer data) {
    GtkWidget *window = gtk_widget_get_toplevel(widget);
    gtk_widget_destroy(window);
}

void create_create_account_window(){
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "創建帳號");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 600, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    error_label = gtk_label_new(NULL); 

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    // 創建標題標籤
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

    gtk_box_pack_start(GTK_BOX(vbox), error_label, FALSE, FALSE, 0);

    // 將標題和副標題添加到垂直框架容器
    gtk_box_pack_start(GTK_BOX(vbox), title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), subtitle, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *username_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), username_entry, FALSE, FALSE, 0);
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");

    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), password_entry, FALSE, FALSE, 0);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");

    GtkWidget *confirm_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(confirm_entry), FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), confirm_entry, FALSE, FALSE, 0);
    gtk_entry_set_placeholder_text(GTK_ENTRY(confirm_entry), "Confirm Password");

    GtkWidget *button_cancel = gtk_button_new_with_label("Cancel");
    gtk_box_pack_start(GTK_BOX(vbox), button_cancel, FALSE, FALSE, 0);
    g_signal_connect(button_cancel, "clicked", G_CALLBACK(on_cancel_clicked2), NULL);

    GtkWidget *button_sign = gtk_button_new_with_label("Sign Up");
    gtk_box_pack_start(GTK_BOX(vbox), button_sign, FALSE, FALSE, 0);
    g_signal_connect(button_sign, "clicked", G_CALLBACK(create_account), NULL);

    gtk_widget_show_all(window);

    gtk_main();
};

void on_button2_clicked(GtkWidget *widget, gpointer data){
    GtkWidget *current_window = gtk_widget_get_toplevel(widget);
    gtk_widget_destroy(current_window);

    create_create_account_window();
};


