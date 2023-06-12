   add_win = create_addwin(data);
}
GtkWidget *create_addwin(gpointer *data){//Open add data's window
   GtkWidget *win, *vbox, *grid, *hbox, *label, *button;
  
   // Create a new dialog window with buttons titled "Add"
   win = gtk_dialog_new_with_buttons("Add", GTK_WINDOW(window), GTK_DIALOG_MODAL, NULL, NULL);
   gtk_container_set_border_width(GTK_CONTAINER(win), 10);
   gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);


   GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(win));


   // Create a vertical box and a grid
   vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
   grid = gtk_grid_new();
   gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
   gtk_grid_set_column_spacing(GTK_GRID(grid), 5);


   // Create labels and entry fields for each data field
   label = gtk_label_new("Name");
   gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
   entry_name = gtk_entry_new();
   gtk_grid_attach(GTK_GRID(grid), entry_name, 1, 0, 1, 1);
	/*Ｏmit team, GP, FG%, 3P%, PPG, SPG*/
   hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);


   // Create "Ok" button and connect the callback function
   button = gtk_button_new_with_label("Ok");
   g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_ok_clicked), data);
   gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 3);
  
   // Create "Cancel" button and connect the callback function
   button = gtk_button_new_with_label("Cancel");
   g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_cancel_clicked), NULL);
   gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 3);


   // Pack the grid and hbox into the vbox
   gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 5);
   gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);
   gtk_container_add(GTK_CONTAINER(content_area), vbox);


   // Connect the "delete_event" signal to destroy the window
   g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(gtk_widget_destroy), win);


   // Show all the widgets in the window
   gtk_widget_show_all(win);


   return win;
}
void on_ok_clicked(GtkWidget *button, gpointer data){//click "Ok" button
   GtkListStore *store;
   GtkTreeIter iter;
   GtkTreeModel *model;


   const gchar *name = gtk_entry_get_text(GTK_ENTRY(entry_name));


   store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
   model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));


   // conversion type
   const gchar *team = gtk_entry_get_text(GTK_ENTRY(entry_team));
   gint gp = atoi(gtk_entry_get_text(GTK_ENTRY(entry_gp)));
   gfloat fg = atof(gtk_entry_get_text(GTK_ENTRY(entry_fg)));
   		/*Ｏmit p, ppg, spg*/
   gboolean exists = FALSE;
   gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
   
   //check if the data exists
   while (valid){
        gchar *existingName;
        gtk_tree_model_get(model, &iter, LIST_NAME, &existingName, -1);


        if (g_strcmp0(existingName, name) == 0){
               exists = TRUE;
               g_free(existingName);
               break;
           }


         g_free(existingName);


         valid = gtk_tree_model_iter_next(model, &iter);


       if (exists){
           GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Data exists");
           gtk_dialog_run(GTK_DIALOG(dialog));
           gtk_widget_destroy(dialog);
           return;
       }
       gtk_list_store_append(store, &iter);


       gtk_list_store_set(store, &iter, LIST_NAME, name, LIST_TEAM, team, LIST_GP, gp, LIST_FG, fg, LIST_P, p, LIST_PPG, ppg, LIST_SPG, spg, -1);
       // add new data
       gtk_widget_destroy(add_win);
   }
}
