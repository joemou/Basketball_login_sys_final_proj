#include <gtk/gtk.h>

void on_cell_activated(GtkEntry *entry, gpointer user_data)
{
    gchar *new_text = g_strdup(gtk_entry_get_text(entry));
    g_print("Cell edited: %s\n", new_text);
    g_free(new_text);
}

void on_add_row_button_clicked(GtkButton *button, gpointer user_data)
{
    static gint rows = 3;
    GtkWidget *grid = GTK_WIDGET(user_data);

    // 創框框
    for (int col = 0; col < 3; col++) {
        GtkWidget *entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), entry, col, rows, 1, 1);
        g_signal_connect(entry, "activate", G_CALLBACK(on_cell_activated), NULL);
    }

    // 增加行
    rows++;
    gtk_widget_show_all(GTK_WIDGET(grid));
}

void on_add_column_button_clicked(GtkButton *button, gpointer user_data)
{
    static gint columns = 3; 
    GtkWidget *grid = GTK_WIDGET(user_data);

    // 創框框
    for (int row = 0; row < 4; row++) {
        GtkWidget *entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), entry, columns, row, 1, 1);
        g_signal_connect(entry, "activate", G_CALLBACK(on_cell_activated), NULL);
    }

    // 增加列
    columns++;
    gtk_widget_show_all(GTK_WIDGET(grid));
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "表格");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 建立表格
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // 表頭
    GtkWidget *header1 = gtk_label_new("列1");
    GtkWidget *header2 = gtk_label_new("列2");
    GtkWidget *header3 = gtk_label_new("列3");
    gtk_grid_attach(GTK_GRID(grid), header1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), header2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), header3, 2, 0, 1, 1);

    // 圖片
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("S__4210692.jpg", NULL);
    if (pixbuf != NULL) {
    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
    g_object_unref(pixbuf);
    gtk_grid_attach(GTK_GRID(grid), image, 0, 1, 1, 1);
    } else {
    g_print("圖片無法顯示\n");
    }
    
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            GtkWidget *entry = gtk_entry_new();
            gtk_grid_attach(GTK_GRID(grid), entry, col, row + 1, 1, 1);
            g_signal_connect(entry, "activate", G_CALLBACK(on_cell_activated), NULL);
        }
    }

    // 增加行按鈕
    GtkWidget *addRowButton = gtk_button_new_with_label("增加行");
    g_signal_connect(addRowButton, "clicked", G_CALLBACK(on_add_row_button_clicked), grid);
    gtk_grid_attach(GTK_GRID(grid), addRowButton, 0, 4, 1, 1);

    // 增加列按鈕
    GtkWidget *addColumnButton = gtk_button_new_with_label("增加列");
    g_signal_connect(addColumnButton, "clicked", G_CALLBACK(on_add_column_button_clicked), grid);
    gtk_grid_attach(GTK_GRID(grid), addColumnButton, 3, 0, 1, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

