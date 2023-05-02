

#include <gtk/gtk.h>

int main(int argc, char *argv[]){
	gtk_init(&argc, &argv);

	GtkWidget *window;
	GtkWidget *fixed;

	GtkWidget *button1;
	GtkWidget *entry1;
	GtkWidget *entry2;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

        fixed = gtk_fixed_new();
	
        button1 = gtk_button_new_with_label("SIGN IN");
	entry1 = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Username"); 
	entry2 = gtk_entry_new();	
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Password");
	gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);

        gtk_fixed_put(GTK_FIXED(fixed), button1, 100, 50);
	gtk_fixed_put(GTK_FIXED(fixed), entry1, 100, 100);
	gtk_fixed_put(GTK_FIXED(fixed), entry2, 100, 200);

        gtk_fixed_move(GTK_FIXED(fixed), button1, 125, 400);

        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        gtk_container_add(GTK_CONTAINER(window), fixed);
        gtk_widget_show_all(window);

        gtk_main();
		
	
	return 0;
}
