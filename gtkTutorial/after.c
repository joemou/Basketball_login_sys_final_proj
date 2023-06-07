#include <gtk/gtk.h>
#include "after.h"

#define isContent1Visible TRUE

//點兩下取消選取的row
void double_click_row(GtkTreeView *list, GtkTreePath *path, GtkTreeViewColumn *column, gpointer selection) {
    
     gtk_tree_selection_unselect_all(selection);    
}

void after_search_activate(GtkWidget *widget, gpointer label)
{
    GtkListStore *store;
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));
    
    GtkTreeSelection *treeSelection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
    if (gtk_tree_selection_get_selected(treeSelection, &model, &iter))// 如果有選中行
    {
        gtk_list_store_remove(store, &iter);// 從模型中移除該行
        //印出 Delete success
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Delete success");
        gtk_dialog_run(GTK_DIALOG(dialog));// 運行對話框，直到關閉 
        gtk_widget_destroy(dialog);// 關閉對話框
    }
    else
    {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Not found");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

int on_search_activate(GtkEntry *entry, gpointer data) {
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
            return 1;
        }
        g_free(nameLower);
        g_free(name);

        valid = gtk_tree_model_iter_next(model, &iter);
    }
    g_free(searchLower);
}

void on_ok_clicked(GtkWidget *button, gpointer data)
{
    GtkListStore *store;
    GtkTreeIter iter;
    GtkTreeModel *model;

    const gchar *name = gtk_entry_get_text(GTK_ENTRY(entry_name));
    
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    //轉換型態
    const gchar *team = gtk_entry_get_text(GTK_ENTRY(entry_team));
    gint gp = atoi(gtk_entry_get_text(GTK_ENTRY(entry_gp)));   
    gfloat fg = atof(gtk_entry_get_text(GTK_ENTRY(entry_fg)));
    gfloat p = atof(gtk_entry_get_text(GTK_ENTRY(entry_p)));
    gfloat ppg = atof(gtk_entry_get_text(GTK_ENTRY(entry_ppg)));   
    gfloat spg = atoi(gtk_entry_get_text(GTK_ENTRY(entry_spg)));   
    
    gboolean exists = FALSE;
    gboolean valid = gtk_tree_model_get_iter_first(model, &iter);

    while (valid) {
        gchar *existingName;
        gtk_tree_model_get(model, &iter, LIST_NAME, &existingName, -1);

        if (g_strcmp0(existingName, name) == 0) {
            exists = TRUE;
            g_free(existingName);
            break;
        }

        g_free(existingName);

        valid = gtk_tree_model_iter_next(model, &iter);
    }

    if (exists) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Data exists");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))
    {
        // 如果有選中行
        gtk_list_store_set(store, &iter, LIST_NAME, name, LIST_TEAM, team, LIST_GP, gp, LIST_FG, fg, LIST_P, p, LIST_PPG, ppg, LIST_SPG, spg, -1);
        // 更新該行的數據
    }
    else
    {
        // 如果沒有選中行
        gtk_list_store_append(store, &iter); 
        // 在模型末尾添加一行
        gtk_list_store_set(store, &iter, LIST_NAME, name, LIST_TEAM, team, LIST_GP, gp, LIST_FG, fg, LIST_P, p, LIST_PPG, ppg, LIST_SPG, spg, -1);
        // 設置新行的數據
        gtk_widget_destroy(add_win);
    }
} 

void on_cancel_clicked(GtkWidget *button, gpointer data)
{
    gtk_widget_destroy(add_win);
}

//add的視窗 
GtkWidget *create_addwin(gpointer *data)
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

    label = gtk_label_new("team");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    entry_team = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_team, 1, 1, 1, 1);

    label = gtk_label_new("GP");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    entry_gp = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_gp, 1, 2, 1, 1);

    label = gtk_label_new("FG%");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
    entry_fg = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_fg, 1, 3, 1, 1);

    label = gtk_label_new("3P%");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
    entry_p = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_p, 1, 4, 1, 1);

    label = gtk_label_new("PPG");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 1, 1);
    entry_ppg = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_ppg, 1, 5, 1, 1);

    label = gtk_label_new("SPG");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 6, 1, 1);
    entry_spg = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_spg, 1, 6, 1, 1);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    button = gtk_button_new_with_label("Ok"); 
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_ok_clicked), data);   
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
    add_win = create_addwin(data);
}

void remove_item(GtkWidget *widget, gpointer selection)
{
    GtkWidget *searchEntry, *win;
    GtkListStore *store;
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win), "Delete");
   
    searchEntry = gtk_search_entry_new();

    gtk_container_add(GTK_CONTAINER(win), searchEntry);
    
    //會先查list中有沒有符合搜尋條件的資料
    g_signal_connect(G_OBJECT(searchEntry), "activate", G_CALLBACK(on_search_activate), list);
    //如果有查到就會執行刪除的動作
    g_signal_connect(G_OBJECT(searchEntry), "activate", G_CALLBACK(after_search_activate), NULL);
    g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(gtk_widget_destroy), win);

    gtk_widget_show_all(win);
}

void edit_item(GtkWidget *widget, gpointer data)
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
        gchar *name, *team;
        gint gp;
        gfloat p, ppg, fg, spg;
        
        gtk_tree_model_get(model, &iter, LIST_NAME, &name, LIST_TEAM, &team, LIST_GP, &gp, LIST_FG, &fg, LIST_P, &p, LIST_PPG, &ppg, LIST_SPG, &spg, -1);
    
        gchar *gp_str = g_strdup_printf("%d", gp);
        gchar *fg_str = g_strdup_printf("%f", fg);
        gchar *p_str = g_strdup_printf("%f", p);
        gchar *ppg_str = g_strdup_printf("%f", ppg);
        gchar *spg_str = g_strdup_printf("%f", spg);        
        
        //打開add的視窗
        add_win = create_addwin(data);
        
        //輸入數據
        gtk_entry_set_text(GTK_ENTRY(entry_name), name);
        gtk_entry_set_text(GTK_ENTRY(entry_team), team);      
        gtk_entry_set_text(GTK_ENTRY(entry_gp), gp_str);      
        gtk_entry_set_text(GTK_ENTRY(entry_fg), fg_str);
        gtk_entry_set_text(GTK_ENTRY(entry_p), p_str);       
        gtk_entry_set_text(GTK_ENTRY(entry_ppg), ppg_str);               
        gtk_entry_set_text(GTK_ENTRY(entry_spg), spg_str);                
    
	    g_free(name);
        g_free(team);
        g_free(gp_str);
        g_free(fg_str);
        g_free(p_str);
        g_free(ppg_str);
        g_free(spg_str);                 
    }
}

//測試column可不可以點擊
void column_clicked(GtkTreeViewColumn *column, gpointer data)
{
    const gchar *title = gtk_tree_view_column_get_title(column);
    g_print("%s\n", title);
}

void init_list(GtkWidget *list, int flag)
{
    GtkCellRenderer *renderer;  
    GtkTreeViewColumn *column1, *column2, *column3, *column4, *column5, *column6, *column7;
    GtkListStore *store;
    
    renderer = gtk_cell_renderer_text_new();
    column1 = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", LIST_NAME, NULL);// 創建一個帶有屬性的樹視圖列，顯示 "Name"，屬性為 LIST_NAME
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column1);// 將列添加到樹視圖中
    g_signal_connect(column1, "clicked", G_CALLBACK(column_clicked), NULL);// 連接列的 "clicked" 信號，當點擊列時調用 column_clicked 函數
    
    renderer = gtk_cell_renderer_text_new(); 
    column2 = gtk_tree_view_column_new_with_attributes("Team", renderer, "text", LIST_TEAM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column2);   
    g_signal_connect(column2, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new(); 
    column7 = gtk_tree_view_column_new_with_attributes("GP", renderer, "text", LIST_GP, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column7);    
    g_signal_connect(column7, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();    
    column3 = gtk_tree_view_column_new_with_attributes("FG%", renderer, "text", LIST_FG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column3);    
    g_signal_connect(column3, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();    
    column4 = gtk_tree_view_column_new_with_attributes("3P%", renderer, "text", LIST_P, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column4);    
    g_signal_connect(column4, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();    
    column5 = gtk_tree_view_column_new_with_attributes("PPG", renderer, "text", LIST_PPG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column5);    
    g_signal_connect(column5, "clicked", G_CALLBACK(column_clicked), NULL);
    
    renderer = gtk_cell_renderer_text_new();   
    column6 = gtk_tree_view_column_new_with_attributes("SPG", renderer, "text", LIST_SPG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column6);    
    g_signal_connect(column6, "clicked", G_CALLBACK(column_clicked), NULL);
    
    if(flag == 1)		//0:標籤不可點, 1:標籤可點
    {
    	gtk_tree_view_column_set_clickable(column1, TRUE);
    	gtk_tree_view_column_set_clickable(column2, TRUE);
    	gtk_tree_view_column_set_clickable(column3, TRUE);
    	gtk_tree_view_column_set_clickable(column7, TRUE);
    	gtk_tree_view_column_set_clickable(column4, TRUE);
        gtk_tree_view_column_set_clickable(column5, TRUE);
        gtk_tree_view_column_set_clickable(column6, TRUE);
    }
    
    store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_FLOAT, G_TYPE_FLOAT, G_TYPE_FLOAT, G_TYPE_FLOAT);
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

    g_object_unref(store);    
}

void traverse_all(GtkWidget *widget, gpointer data)
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);// 創建可滾動的視窗
    
    gtk_window_set_title(GTK_WINDOW(window), "Traverse");//標題
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);

    GtkWidget *tree_view = gtk_tree_view_new();
    init_list(tree_view, 0);		//0:標籤不可點
  
    // 設置滾動窗口的滾動策略為自動
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    gtk_widget_show_all(window);    
}

void create_after_window() {
    GtkWidget *sw, *remove, *add, *edit, *io, *traverse , *vbox, *hbox, *searchEntry;
   
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
    traverse = gtk_button_new();

    GtkWidget *addImage = gtk_image_new_from_file("add.png");
    gtk_button_set_image(GTK_BUTTON(add), addImage);

    GtkWidget *editImage = gtk_image_new_from_file("edit.png");
    gtk_button_set_image(GTK_BUTTON(edit), editImage);

    GtkWidget *removeImage = gtk_image_new_from_file("remove.png");
    gtk_button_set_image(GTK_BUTTON(remove), removeImage);

    GtkWidget *ioImage = gtk_image_new_from_file("io.png");
    gtk_button_set_image(GTK_BUTTON(io), ioImage);

    GtkWidget *traverseImage = gtk_image_new_from_file("traverse.png");
    gtk_button_set_image(GTK_BUTTON(traverse), traverseImage);

    gtk_box_pack_start(GTK_BOX(hbox), add, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), remove, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), edit, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), io, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), traverse, TRUE, TRUE, 3);

    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 3);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    init_list(list, 0);

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
    
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(searchEntry), "activate", G_CALLBACK(on_search_activate), list);
    g_signal_connect(G_OBJECT(add), "clicked", G_CALLBACK(append_item), "append");
    g_signal_connect(G_OBJECT(remove), "clicked", G_CALLBACK(remove_item), selection);
    g_signal_connect(G_OBJECT(edit), "clicked", G_CALLBACK(edit_item), selection); 
    g_signal_connect(G_OBJECT(traverse), "clicked", G_CALLBACK(traverse_all), NULL);  
    

    gtk_widget_show_all(window);

    gtk_main();

}

//會開啟這個檔案的視窗
void on_button1_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *current_window = gtk_widget_get_toplevel(widget);
    gtk_widget_destroy(current_window);

    create_after_window();
}
