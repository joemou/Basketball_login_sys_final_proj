#include <gtk/gtk.h>
#include "merge_sort.h"
#include "basic_func.h"
#include "edit_json.h"
#include "after.h"
#include "cJSON.h"
#include "avl.h"

#define isContent1Visible TRUE
#define debug g_print("debug %d\n", __LINE__)

GtkWidget *list, *add_win, *entry_name, *entry_gp, *entry_fpg, *entry_ppg, *entry_spg, *entry_tpp, *window;
GtkTreeSelection *selection;
char *find_team = "Los Angeles Lakers";
cJSON *teams_data; // complete data base
cJSON *authed_team; // data base of particular team

node *head = NULL;
node *root = NULL;

void insert_AVL_to_gtk()
{
    node *temp = head;

    while(temp!=NULL){
        GtkListStore *store;
        GtkTreeIter iter;
        GtkTreeModel *model;

        const gchar *name = temp->name;
        gint gp = temp->game_played;
        gdouble fgp = temp->feiled_goal_percentage;
        gdouble ppg = temp->points_per_game;
        gdouble spg = temp->steal_per_game;
        gdouble tpp = temp->three_point_percentage;

        store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
        model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

        temp = temp->next;

        gtk_list_store_append(store, &iter); 
        gtk_list_store_set(store, &iter, LIST_NAME, name, LIST_GP, gp, LIST_FPG, fgp, LIST_PPG, ppg, LIST_SPG, spg, LIST_TPP, tpp, -1);
    }
}

void insert_json_to_AVL(char *teamName)
{
    int time, game_played;
    float feiled_goal_percentage, three_point_percentage, points_per_game, steal_per_game;

    char *name;

    char *data = read_json_to_str("data.json");
    teams_data = cJSON_Parse(data);
    cJSON *Basket_Ball_Teams = cJSON_GetObjectItem(teams_data, "Basket_Ball_Teams");
    int teamSize = cJSON_GetArraySize(Basket_Ball_Teams);
    // find team
    for(int i = 0; i < teamSize; i++){
        cJSON *team = cJSON_GetArrayItem(Basket_Ball_Teams, i);
        char *getName = cJSON_GetStringValue(cJSON_GetObjectItem(team, "Team Name"));
        if(strcmp(getName, teamName) == 0){
            authed_team = cJSON_GetObjectItem(team, "Players");
            break;
        }
    }
    int size = cJSON_GetArraySize(authed_team);
    for(int i = 0; i < size; ++i){
        cJSON *tmp = cJSON_GetArrayItem(authed_team, i);
        name = cJSON_GetStringValue(cJSON_GetObjectItem(tmp, "Name"));
        game_played = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "GP"));
        feiled_goal_percentage = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "FG"));
        three_point_percentage = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "3P"));
        points_per_game = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "PPG"));
        steal_per_game = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "SPG"));
        create(&head, name, game_played, feiled_goal_percentage, three_point_percentage, points_per_game, steal_per_game);//create link list
        root = insert(root,head);//create avl tree
    }
}

void insert_data_to_data_base(const gchar *name, gint gp, gdouble fpg, gdouble ppg, gdouble spg, gdouble tpp)
{
    // add to AVL
    create(&head, name, gp, fpg, tpp, ppg, spg);
    root = insert(root,head);
    // add to JSON
    cJSON *player = cJSON_CreateObject();
    cJSON_AddStringToObject(player, "Name", name);
    cJSON_AddNumberToObject(player, "GP", gp);
    cJSON_AddNumberToObject(player, "3P", tpp);
    cJSON_AddNumberToObject(player, "PPG", ppg);
    cJSON_AddNumberToObject(player, "FG", fpg);
    cJSON_AddNumberToObject(player, "SPG", spg);
    
    cJSON_AddItemToArray(authed_team, player);
    FILE *file = fopen("data.json", "w");
    fputs(cJSON_Print(teams_data), file);
    fclose(file);
}

void remove_data_from_data_base(const char *search_name)
{
    // delete from avl
    delete(&head, head, root, search_name);
    // delete from json
    int size = cJSON_GetArraySize(authed_team);
    for(int i = 0; i < size; ++i){
        cJSON *tmp = cJSON_GetArrayItem(authed_team, i);
        char *player = cJSON_GetStringValue(cJSON_GetObjectItem(tmp, "Name"));
        if(strcmp(player, search_name) == 0){
            cJSON_DeleteItemFromArray(authed_team, i);
            break;
        }
    }
    FILE *file = fopen("data.json", "w");
    fputs(cJSON_Print(teams_data), file);
    fclose(file);
}

void double_click_row(GtkTreeView *list, GtkTreePath *path, GtkTreeViewColumn *column, gpointer selection)
{    
    gtk_tree_selection_unselect_all(selection);    
}

void on_ok_clicked(GtkWidget *button, gpointer data)
{
    GtkListStore *store;
    GtkTreeIter iter;
    GtkTreeModel *model;

    const gchar *name = gtk_entry_get_text(GTK_ENTRY(entry_name));
    gint gp = atoi(gtk_entry_get_text(GTK_ENTRY(entry_gp)));   
    gdouble fpg = atof(gtk_entry_get_text(GTK_ENTRY(entry_fpg)));
    gdouble ppg = atof(gtk_entry_get_text(GTK_ENTRY(entry_ppg)));
    gdouble spg = atoi(gtk_entry_get_text(GTK_ENTRY(entry_spg)));
    gdouble tpp = atoi(gtk_entry_get_text(GTK_ENTRY(entry_tpp)));

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))
    {
        // case of edit
        gtk_list_store_set(store, &iter, LIST_NAME, name, LIST_GP, gp, LIST_FPG, fpg, LIST_PPG, ppg, LIST_SPG, spg, LIST_TPP, tpp, -1);
        remove_data_from_data_base(name);
        insert_data_to_data_base(name, gp, fpg, ppg, spg, tpp);
    }
    else
    {
        // case of add
        gtk_list_store_append(store, &iter); 
        gtk_list_store_set(store, &iter, LIST_NAME, name, LIST_GP, gp, LIST_FPG, fpg, LIST_PPG, ppg, LIST_SPG, spg, LIST_TPP, tpp, -1);
        insert_data_to_data_base(name, gp, fpg, ppg, spg, tpp);
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
    entry_fpg = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_fpg, 1, 2, 1, 1);
    label = gtk_label_new("PPG");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
    entry_ppg = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_ppg, 1, 3, 1, 1);
    label = gtk_label_new("TP");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
    entry_spg = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_spg, 1, 4, 1, 1);
    label = gtk_label_new("FGM");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 1, 1);
    entry_tpp = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_tpp, 1, 5, 1, 1);

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
        gint gp;
        gdouble fpg, ppg, spg, tpp;
        
        gtk_tree_model_get(model, &iter, LIST_NAME, &name, LIST_GP, &gp, LIST_FPG, &fpg, LIST_PPG, &ppg, LIST_SPG, &spg, LIST_TPP, &tpp, -1);
    
        gchar *gp_str = g_strdup_printf("%d", gp);
        gchar *fpg_str = g_strdup_printf("%f", fpg);
        gchar *ppg_str = g_strdup_printf("%f", ppg);
        gchar *spg_str = g_strdup_printf("%f", spg);
        gchar *tpp_str = g_strdup_printf("%f", tpp);
        
        add_win = create_addwin();
        
        gtk_entry_set_text(GTK_ENTRY(entry_name), name);
        gtk_entry_set_text(GTK_ENTRY(entry_gp), gp_str);
        gtk_entry_set_text(GTK_ENTRY(entry_fpg), fpg_str);
        gtk_entry_set_text(GTK_ENTRY(entry_ppg), ppg_str);
        gtk_entry_set_text(GTK_ENTRY(entry_spg), spg_str);
        gtk_entry_set_text(GTK_ENTRY(entry_tpp), tpp_str);
    
	    g_free(name);
        g_free(gp_str);
        g_free(fpg_str);
        g_free(ppg_str);
        g_free(spg_str);
        g_free(tpp_str);        
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
    column = gtk_tree_view_column_new_with_attributes("FPG", renderer, "text", LIST_FPG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();    
    column = gtk_tree_view_column_new_with_attributes("PPG", renderer, "text", LIST_PPG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();    
    column = gtk_tree_view_column_new_with_attributes("SPG", renderer, "text", LIST_SPG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();   
    column = gtk_tree_view_column_new_with_attributes("TPP", renderer, "text", LIST_TPP, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    gtk_tree_view_column_set_clickable(column, TRUE);
    g_signal_connect(column, "clicked", G_CALLBACK(column_clicked), NULL);
    
    store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_INT, G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_DOUBLE);
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

    insert_json_to_AVL(find_team);
    insert_AVL_to_gtk();

    g_object_unref(store);    
}

void on_search_activate(GtkEntry *entry, gpointer data)
{
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

void create_after_window(const gchar *username)
{
    GtkWidget *sw, *remove, *add, *edit, *io, *print_all , *vbox, *hbox, *searchEntry;
    // uncomment when fixed
    // find_team = username;
   
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Player Data");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 600, 600);

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
    io = gtk_button_new();
    print_all = gtk_button_new();

    GtkWidget *addImage = gtk_image_new_from_file("add.png");
    gtk_button_set_image(GTK_BUTTON(add), addImage);

    GtkWidget *editImage = gtk_image_new_from_file("edit.png");
    gtk_button_set_image(GTK_BUTTON(edit), editImage);

    GtkWidget *removeImage = gtk_image_new_from_file("remove.png");
    gtk_button_set_image(GTK_BUTTON(remove), removeImage);

    GtkWidget *ioImage = gtk_image_new_from_file("printall.png");
    gtk_button_set_image(GTK_BUTTON(io), ioImage);

    GtkWidget *printallImage = gtk_image_new_from_file("io.png");
    gtk_button_set_image(GTK_BUTTON(print_all), printallImage);

    gtk_box_pack_start(GTK_BOX(hbox), add, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), remove, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), edit, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), io, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), print_all, TRUE, TRUE, 3);

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