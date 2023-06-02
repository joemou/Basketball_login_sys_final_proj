#include <gtk/gtk.h>
#include <stdio.h>
#include "after.h"
#include "cJSON.h"
#include "edit_json.h"
#include "sign_in.h"

#define debug printf("hi");
#define isContent1Visible TRUE

GtkWidget *list, *add_win, *entry_name, *entry_gp, *entry_mpg, *entry_ppg, *entry_tp, *entry_fgm, *entry_fg, *entry_pm, *entry_to, *entry_pf, *window;
GtkTreeSelection *selection;

void double_click_row(GtkTreeView *list, GtkTreePath *path, GtkTreeViewColumn *column, gpointer selection) {
    
     gtk_tree_selection_unselect_all(selection);    
}

void show_data() {
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    debug;
    // reads from json for tmp
    char *data = read_json_to_str("data.json");
    cJSON *team = cJSON_Parse(data);
    cJSON *team1 = cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(team, "Basket_Ball_Teams"), 0), "Players");
    int size = cJSON_GetArraySize(team1);
    for(int i = 0; i < size; ++i){
        cJSON *tmp = cJSON_GetArrayItem(team1, i);
        char *name = cJSON_GetStringValue(cJSON_GetObjectItem(tmp, "Player Name"));
        int gp = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "game_played"));
        
        gtk_list_store_append(store, &iter); 
        gtk_list_store_set(store, &iter, LIST_NAME, name, LIST_GP, gp);
    }
}

void on_ok_clicked(GtkWidget *button, gpointer data)
{
    GtkListStore *store;
    GtkTreeIter iter;
    GtkTreeModel *model;

    const gchar *name = gtk_entry_get_text(GTK_ENTRY(entry_name));
    gint gp = atoi(gtk_entry_get_text(GTK_ENTRY(entry_gp)));   
    gdouble mpg = atof(gtk_entry_get_text(GTK_ENTRY(entry_mpg)));
    gdouble ppg = atof(gtk_entry_get_text(GTK_ENTRY(entry_ppg)));
    gint tp = atoi(gtk_entry_get_text(GTK_ENTRY(entry_tp)));
    gint fgm = atoi(gtk_entry_get_text(GTK_ENTRY(entry_fgm)));
    gdouble fg = atof(gtk_entry_get_text(GTK_ENTRY(entry_fg)));
    gint pm = atoi(gtk_entry_get_text(GTK_ENTRY(entry_pm)));
    gint to = atoi(gtk_entry_get_text(GTK_ENTRY(entry_to)));
    gint pf = atoi(gtk_entry_get_text(GTK_ENTRY(entry_pf)));

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))
    {
        gtk_list_store_set(store, &iter, LIST_NAME, name, LIST_GP, gp, LIST_MPG, mpg, LIST_PPG, ppg, LIST_TP, tp, LIST_FGM, fgm, LIST_FG, fg, LIST_PM, pm, LIST_TO, to, LIST_PF, pf, -1);    }
    else
    {
        gtk_list_store_append(store, &iter); 
        gtk_list_store_set(store, &iter, LIST_NAME, name, LIST_GP, gp, LIST_MPG, mpg, LIST_PPG, ppg, LIST_TP, tp, LIST_FGM, fgm, LIST_FG, fg, LIST_PM, pm, LIST_TO, to, LIST_PF, pf, -1);
    }

    gtk_widget_destroy(add_win);
}

void on_cancel_clicked(GtkWidget *button, gpointer data)
{
    gtk_widget_destroy(add_win);
}

GtkWidget *create_addwin()
{
    GtkWidget *win, *vbox, *grid, *hbox, *label, *button;

    win = gtk_dialog_new_with_buttons("Add", GTK_WINDOW(window), GTK_DIALOG_MODAL, NULL, NULL);
    gtk_container_set_border_width(GTK_CONTAINER(win), 10);
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(win));

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
    label = gtk_label_new("MPG");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    entry_mpg = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_mpg, 1, 2, 1, 1);
    label = gtk_label_new("PPG");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
    entry_ppg = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_ppg, 1, 3, 1, 1);
    label = gtk_label_new("TP");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
    entry_tp = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_tp, 1, 4, 1, 1);
    label = gtk_label_new("FGM");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 1, 1);
    entry_fgm = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_fgm, 1, 5, 1, 1);
    label = gtk_label_new("FG%");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 6, 1, 1);
    entry_fg = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_fg, 1, 6, 1, 1);
    label = gtk_label_new("3PM");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 7, 1, 1);
    entry_pm = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_pm, 1, 7, 1, 1);
    label = gtk_label_new("TO");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 8, 1, 1);
    entry_to = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_to, 1, 8, 1, 1);
    label = gtk_label_new("PF");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 9, 1, 1);
    entry_pf = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_pf, 1, 9, 1, 1);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    button = gtk_button_new_with_label("Ok");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_ok_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 3);
    button = gtk_button_new_with_label("Cancel");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_cancel_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 3);

    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);
    gtk_container_add(GTK_CONTAINER(content_area), vbox);

    g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(gtk_widget_destroy), win);

    // show_data();

    gtk_widget_show_all(win);

    return win;
}

void append_item(GtkWidget *widget, gpointer data)
{
    add_win = create_addwin();
}

void remove_item(GtkWidget *widget, gpointer selection)
{

    GtkListStore *store;
    GtkTreeModel *model;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    if (gtk_tree_model_get_iter_first(model, &iter) == FALSE)
    {
        return;
    }

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))
    {
        gtk_list_store_remove(store, &iter);
    }    
}

void edit_item(GtkWidget *widget, gpointer selection)
{
    GtkListStore *store;
    GtkTreeModel *model;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    if (gtk_tree_model_get_iter_first(model, &iter) == FALSE)
    {
        return;
    }

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))
    {   
        gchar *name;
        gint gp, tp, fgm, pm, to, pf;
        gdouble mpg, ppg, fg;
        
        gtk_tree_model_get(model, &iter, LIST_NAME, &name, LIST_GP, &gp, LIST_MPG, &mpg, LIST_PPG, &ppg, LIST_TP, &tp, LIST_FGM, &fgm, LIST_FG, &fg, LIST_PM, &pm, LIST_TO, &to, LIST_PF, &pf, -1);
    
        gchar *gp_str = g_strdup_printf("%d", gp);
        gchar *mpg_str = g_strdup_printf("%f", mpg);
        gchar *ppg_str = g_strdup_printf("%f", ppg);
        gchar *tp_str = g_strdup_printf("%d", tp);
        gchar *fgm_str = g_strdup_printf("%d", fgm);
        gchar *fg_str = g_strdup_printf("%f", fg);
        gchar *pm_str = g_strdup_printf("%d", pm);
        gchar *to_str = g_strdup_printf("%d", to);
        gchar *pf_str = g_strdup_printf("%d",pf);	
        
        add_win = create_addwin();
        
        gtk_entry_set_text(GTK_ENTRY(entry_name), name);      
        gtk_entry_set_text(GTK_ENTRY(entry_gp), gp_str);
        gtk_entry_set_text(GTK_ENTRY(entry_mpg), mpg_str);       
        gtk_entry_set_text(GTK_ENTRY(entry_ppg), ppg_str);               
        gtk_entry_set_text(GTK_ENTRY(entry_tp), tp_str);            
        gtk_entry_set_text(GTK_ENTRY(entry_fgm), fgm_str);                
        gtk_entry_set_text(GTK_ENTRY(entry_fg), fg_str);              
        gtk_entry_set_text(GTK_ENTRY(entry_pm), pm_str);       
        gtk_entry_set_text(GTK_ENTRY(entry_to), to_str);
        gtk_entry_set_text(GTK_ENTRY(entry_pf), pf_str);
    
	    g_free(name);
        g_free(gp_str);
        g_free(mpg_str);
        g_free(ppg_str);
        g_free(tp_str);
        g_free(fgm_str);
        g_free(fg_str);
        g_free(pm_str);
        g_free(to_str);
        g_free(pf_str);        
        
    }
}

void column_clicked(GtkTreeViewColumn *column, gpointer data)
{
    const gchar *title = gtk_tree_view_column_get_title(column);
    g_print("%s\n", title);
}

void init_list(GtkWidget *list)
{
    GtkCellRenderer *renderer;  
    GtkTreeViewColumn *column;
    GtkListStore *store;
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", LIST_NAME, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new(); 
    column = gtk_tree_view_column_new_with_attributes("GP", renderer, "text", LIST_GP, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();    
    column = gtk_tree_view_column_new_with_attributes("MPG", renderer, "text", LIST_MPG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();    
    column = gtk_tree_view_column_new_with_attributes("PPG", renderer, "text", LIST_PPG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();    
    column = gtk_tree_view_column_new_with_attributes("TP", renderer, "text", LIST_TP, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();   
    column = gtk_tree_view_column_new_with_attributes("FGM", renderer, "text", LIST_FGM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();    
    column = gtk_tree_view_column_new_with_attributes("FG%", renderer, "text", LIST_FG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();    
    column = gtk_tree_view_column_new_with_attributes("3PM", renderer, "text", LIST_PM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();    
    column = gtk_tree_view_column_new_with_attributes("TO", renderer, "text", LIST_TO, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();    
    column = gtk_tree_view_column_new_with_attributes("PF", renderer, "text", LIST_PF, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);   
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_INT, G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_INT, G_TYPE_INT, G_TYPE_DOUBLE, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

    g_object_unref(store);    
}

void on_search_activate(GtkEntry *entry, gpointer data) {
    const gchar *searchText = gtk_entry_get_text(entry);
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(data));
    GtkTreeIter iter;
    gboolean valid;

    // 將搜尋字串轉換為小寫以進行不分大小寫的比對
    gchar *searchLower = g_utf8_strdown(searchText, -1);

    valid = gtk_tree_model_get_iter_first(model, &iter);

    while (valid) {
        gchar *name;
        gtk_tree_model_get(model, &iter, LIST_NAME, &name, -1);

        // 將項目名稱轉換為小寫以進行不分大小寫的比對
        gchar *nameLower = g_utf8_strdown(name, -1);

        if (g_strstr_len(nameLower, -1, searchLower) != NULL) {
            // 符合搜尋條件，將該項目顯示
            gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(data), gtk_tree_model_get_path(model, &iter), NULL, FALSE, 0.0, 0.0);
            gtk_tree_selection_select_iter(gtk_tree_view_get_selection(GTK_TREE_VIEW(data)), &iter);
            g_free(nameLower);
            g_free(name);
            g_free(searchLower);
            return;
        }

        g_free(nameLower);
        g_free(name);

        valid = gtk_tree_model_iter_next(model, &iter);
    }

    g_free(searchLower);
}

void create_after_window() {
    GtkWidget *sw, *remove, *add, *edit, *vbox, *hbox, *searchEntry;
   
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Player Data");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 500, 400);

    searchEntry = gtk_search_entry_new();

    sw = gtk_scrolled_window_new(NULL, NULL);
    list = gtk_tree_view_new();
    gtk_container_add(GTK_CONTAINER(sw), list);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw), GTK_SHADOW_ETCHED_IN);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    
    gtk_box_pack_start(GTK_BOX(vbox), searchEntry, FALSE, FALSE, 3);
    gtk_box_pack_start(GTK_BOX(vbox), sw, TRUE, TRUE, 5);
    

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    add = gtk_button_new();
    remove = gtk_button_new();
    edit = gtk_button_new();

    GtkWidget *addImage = gtk_image_new_from_file("add.png");
    gtk_button_set_image(GTK_BUTTON(add), addImage);

    GtkWidget *editImage = gtk_image_new_from_file("edit.png");
    gtk_button_set_image(GTK_BUTTON(edit), editImage);

    GtkWidget *removeImage = gtk_image_new_from_file("remove.png");
    gtk_button_set_image(GTK_BUTTON(remove), removeImage);

    gtk_box_pack_start(GTK_BOX(hbox), add, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), remove, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), edit, TRUE, TRUE, 3);
    
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 3);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    init_list(list);

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

    g_signal_connect(G_OBJECT(searchEntry), "activate", G_CALLBACK(on_search_activate), list);
    g_signal_connect(G_OBJECT(add), "clicked", G_CALLBACK(append_item), NULL);
    g_signal_connect(G_OBJECT(remove), "clicked", G_CALLBACK(remove_item), selection);
    g_signal_connect(G_OBJECT(edit), "clicked", G_CALLBACK(edit_item), selection);      
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(list, "row-activated", G_CALLBACK(double_click_row), selection);

    gtk_widget_show_all(window);

    gtk_main();

}

void on_button1_clicked(GtkWidget *widget, gpointer data) {

    // call "login.h" and do login check
    struct hash_table table;
    table.size = HASH_SIZE;
    table.users = malloc(sizeof(struct user *) * table.size);
    memset(table.users, 0, sizeof(struct user *) * table.size);

    // load users from file
    load_users(&table, "users.dat");

    int choice, Login_successful = 0;
        
    // read input
    printf("1: Sign up\n2: Login\n");
    
    scanf(" %d", &choice);
    if (choice == 1) {
        create_user(&table);
    } else {
        // authenticate user
        if (find_user(&table)) {
            // login successful
            Login_successful = 1;
        } else {
            // login failed
        }
    }

    // save users to file before exiting
    save_users(&table, "users.dat");

    if(Login_successful) {
        GtkWidget *current_window = gtk_widget_get_toplevel(widget);
        gtk_widget_destroy(current_window);
        create_after_window();
    }
}
