#include <gtk/gtk.h>

void on_file_selected(GtkFileChooserButton *filechooser, gpointer data)
{
    gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooser));
    g_print("Selected file: %s\n", filename);
    g_free(filename);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *filechooser = gtk_file_chooser_button_new("Select File", GTK_FILE_CHOOSER_ACTION_OPEN);
    g_signal_connect(filechooser, "file-set", G_CALLBACK(on_file_selected), NULL);
    gtk_container_add(GTK_CONTAINER(window), filechooser);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
