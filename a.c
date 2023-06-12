GtkWidget *create_addwin() {
    GtkWidget *win, *vbox, *grid, *hbox, *label, *button;

    win = gtk_dialog_new_with_buttons("Add", GTK_WINDOW(window), GTK_DIALOG_MODAL, NULL, NULL);
    gtk_container_set_border_width(GTK_CONTAINER(win), 10);
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(win));

    error_label = gtk_label_new(NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    label = gtk_label_new("Name");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry_name = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_name, 1, 0, 1, 1);

    label = gtk_label_new("GP");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    entry_gp = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_gp, 1, 1, 1, 1);

    label = gtk_label_new("FG%");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    entry_fpg = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_fpg, 1, 2, 1, 1);

    label = gtk_label_new("3P%");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
    entry_tpp = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_tpp, 1, 3, 1, 1);

    label = gtk_label_new("PPG");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
    entry_ppg = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_ppg, 1, 4, 1, 1);

    label = gtk_label_new("SPG");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 1, 1);
    entry_spg = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_spg, 1, 5, 1, 1);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    button = gtk_button_new_with_label("Ok");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_ok_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 3);
    button = gtk_button_new_with_label("Cancel");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_cancel_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 3);

    // gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);
    gtk_container_add(GTK_CONTAINER(content_area), vbox);

    g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(gtk_widget_destroy), win);

    gtk_widget_show_all(win);

    return win;
}