#include "after.h"

#include <gtk/gtk.h>

#include "avl.h"
#include "basic_func.h"
#include "cJSON.h"
#include "edit_json.h"
#include "merge_sort.h"

#define isContent1Visible TRUE
#define debug g_print("debug %d\n", __LINE__)

GtkWidget *list, *add_win, *entry_team, *entry_name, *entry_gp, *entry_fpg, *entry_ppg, *entry_spg, *entry_tpp, *window;
static GtkWidget *error_label;
GtkTreeSelection *selection;
char *find_team = "Los Angeles Lakers";
cJSON *teams_data;   // complete data base
cJSON *authed_team;  // data base of particular team
int not_init = 1;

node *head = NULL;
node *root = NULL;
node *search_player;

void insert_AVL_to_gtk() {
    node *temp = head;

    GtkListStore *store;
    GtkTreeIter iter;
    GtkTreeModel *model;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    while (temp != NULL) {
        const gchar *name = temp->name;
        gint gp = temp->game_played;
        gdouble fgp = temp->feiled_goal_percentage;
        gdouble ppg = temp->points_per_game;
        gdouble spg = temp->steal_per_game;
        gdouble tpp = temp->three_point_percentage;

        temp = temp->next;

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, LIST_TEAM, find_team, LIST_NAME, name, LIST_GP, gp, LIST_FPG, fgp, LIST_PPG, ppg, LIST_SPG, spg, LIST_TPP, tpp, -1);
    }
}

void insert_json_to_AVL(char *teamID) {
    char *name;
    int gp;
    float fgp, tpp, ppg, spg;

    char *data = read_json_to_str("data.json");
    teams_data = cJSON_Parse(data);
    cJSON *Basket_Ball_Teams = cJSON_GetObjectItem(teams_data, "Basket_Ball_Teams");
    int teamSize = cJSON_GetArraySize(Basket_Ball_Teams);
    // find team
    for (int i = 0; i < teamSize; i++) {
        cJSON *team = cJSON_GetArrayItem(Basket_Ball_Teams, i);
        find_team = cJSON_GetStringValue(cJSON_GetObjectItem(team, "Team Name"));
        if (strcmp(find_team, teamID) == 0) {
            authed_team = cJSON_GetObjectItem(team, "Players");
            break;
        }
    }
    int size = cJSON_GetArraySize(authed_team);
    for (int i = 0; i < size; ++i) {
        cJSON *tmp = cJSON_GetArrayItem(authed_team, i);
        name = cJSON_GetStringValue(cJSON_GetObjectItem(tmp, "Name"));
        gp = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "GP"));
        fgp = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "FG"));
        tpp = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "3P"));
        ppg = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "PPG"));
        spg = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "SPG"));
        create(&head, name, gp, fgp, tpp, ppg, spg);  // create link list
        root = insert(root, head);                    // create avl tree
    }
}

void insert_data_to_data_base(const gchar *name, gint gp, gdouble fpg, gdouble ppg, gdouble spg, gdouble tpp) {
    // add to AVL
    create(&head, name, gp, fpg, tpp, ppg, spg);
    root = insert(root, head);
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

void remove_data_from_data_base(const char *search_name) {
    // delete from avl
    delete (&head, head, root, search_name);
    // delete from json
    int size = cJSON_GetArraySize(authed_team);
    for (int i = 0; i < size; ++i) {
        cJSON *tmp = cJSON_GetArrayItem(authed_team, i);
        char *player = cJSON_GetStringValue(cJSON_GetObjectItem(tmp, "Name"));
        if (strcmp(player, search_name) == 0) {
            cJSON_DeleteItemFromArray(authed_team, i);
            break;
        }
    }
    FILE *file = fopen("data.json", "w");
    fputs(cJSON_Print(teams_data), file);
    fclose(file);
}

void delete_table_item() {
    GtkListStore *store;
    GtkTreeModel *model;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    while (gtk_tree_model_get_iter_first(model, &iter)) {
        gtk_list_store_remove(store, &iter);
    }
}

void printInorder(struct node *node) {
    if (node == NULL) {
        return;
    }

    printInorder(node->left);

    GtkListStore *store;
    GtkTreeIter iter;
    GtkTreeModel *model;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    const gchar *name = node->name;
    gint gp = node->game_played;
    gdouble fgp = node->feiled_goal_percentage;
    gdouble ppg = node->points_per_game;
    gdouble spg = node->steal_per_game;
    gdouble tpp = node->three_point_percentage;

    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, LIST_TEAM, find_team, LIST_NAME, name, LIST_GP, gp, LIST_FPG, fgp, LIST_PPG, ppg, LIST_SPG, spg, LIST_TPP, tpp, -1);

    printInorder(node->right);
}

// 點兩下取消選取的row
void double_click_row(GtkTreeView *list, GtkTreePath *path, GtkTreeViewColumn *column, gpointer selection) {
    gtk_tree_selection_unselect_all(selection);
}

void after_search_activate(GtkWidget *widget, gpointer label) {
    GtkListStore *store;
    GtkTreeModel *model;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    GtkTreeSelection *treeSelection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
    if (gtk_tree_selection_get_selected(treeSelection, &model, &iter))  // 如果有選中行
    {
        gchar *item;
        gtk_tree_model_get(model, &iter, 1, &item, -1);
        remove_data_from_data_base(item);
        gtk_list_store_remove(store, &iter);  // 從模型中移除該行
        // 印出 Delete success
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Delete success");
        gtk_dialog_run(GTK_DIALOG(dialog));  // 運行對話框，直到關閉
        gtk_widget_destroy(dialog);          // 關閉對話框
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Not found");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_ok_clicked(GtkWidget *button, gpointer data) {
    GtkListStore *store;
    GtkTreeIter iter;
    GtkTreeModel *model;

    // 轉換型態
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(entry_name));
    gint gp = atoi(gtk_entry_get_text(GTK_ENTRY(entry_gp)));
    gfloat fgp = atof(gtk_entry_get_text(GTK_ENTRY(entry_fpg)));
    gfloat tpp = atof(gtk_entry_get_text(GTK_ENTRY(entry_tpp)));
    gfloat ppg = atof(gtk_entry_get_text(GTK_ENTRY(entry_ppg)));
    gfloat spg = atoi(gtk_entry_get_text(GTK_ENTRY(entry_spg)));

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter)) {
        // case of edit
        gtk_list_store_set(store, &iter, LIST_NAME, name, LIST_GP, gp, LIST_FPG, fgp, LIST_PPG, ppg, LIST_SPG, spg, LIST_TPP, tpp, -1);
        remove_data_from_data_base(name);
        insert_data_to_data_base(name, gp, fgp, ppg, spg, tpp);
    } else {
        // case of add
        gboolean exists = FALSE;
        gboolean valid = gtk_tree_model_get_iter_first(model, &iter);

        gchar *existingName;
        while (valid) {
            gtk_tree_model_get(model, &iter, LIST_NAME, &existingName, -1);

            if (g_strcmp0(existingName, name) == 0) {
                exists = TRUE;
                break;
            }

            valid = gtk_tree_model_iter_next(model, &iter);
        }
        // g_free(existingName);

        if (exists) {
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Data exists");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }
        // 在模型末尾添加一行
        gtk_list_store_append(store, &iter);
        // 設置新行的數據
        gtk_list_store_set(store, &iter, LIST_TEAM, find_team, LIST_NAME, name, LIST_GP, gp, LIST_FPG, fgp, LIST_PPG, ppg, LIST_SPG, spg, LIST_TPP, tpp, -1);
        insert_data_to_data_base(name, gp, fgp, ppg, spg, tpp);
    }
    gtk_widget_destroy(add_win);
}

void on_cancel_clicked(GtkWidget *button, gpointer data) {
    gtk_widget_destroy(add_win);
}

//Open add data's window
GtkWidget *create_addwin() {
    GtkWidget *win, *vbox, *grid, *hbox, *label, *button;

    // Create a new dialog window with buttons titled "Add"
    win = gtk_dialog_new_with_buttons("Add", GTK_WINDOW(window), GTK_DIALOG_MODAL, NULL, NULL);
    gtk_container_set_border_width(GTK_CONTAINER(win), 10);
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(win));

    error_label = gtk_label_new(NULL);

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

void append_item(GtkWidget *widget, gpointer data) {
    add_win = create_addwin();
}

void remove_item(GtkWidget *widget, gpointer selection) {
    GtkWidget *searchEntry, *win;
    GtkListStore *store;
    GtkTreeModel *model;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(win), 60, 60);
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(win), "Delete");

    searchEntry = gtk_search_entry_new();
    gtk_container_add(GTK_CONTAINER(win), searchEntry);

    // 會先查list中有沒有符合搜尋條件的資料
    g_signal_connect(G_OBJECT(searchEntry), "activate", G_CALLBACK(on_search_activate), list);
    // 如果有查到就會執行刪除的動作
    g_signal_connect(G_OBJECT(searchEntry), "activate", G_CALLBACK(after_search_activate), NULL);
    g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(gtk_widget_destroy), win);

    gtk_widget_show_all(win);
}

void edit_item(GtkWidget *widget, gpointer selection) {
    GtkListStore *store;
    GtkTreeModel *model;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) {
        return;
    }

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter)) {
        gchar *name, *team;
        gint gp;
        gfloat tpp, ppg, fpg, spg;

        gtk_tree_model_get(model, &iter, LIST_TEAM, &team, LIST_NAME, &name, LIST_GP, &gp, LIST_FPG, &fpg, LIST_PPG, &ppg, LIST_SPG, &spg, LIST_TPP, &tpp, -1);

        gchar *gp_str = g_strdup_printf("%d", gp);
        gchar *fpg_str = g_strdup_printf("%f", fpg);
        gchar *tpp_str = g_strdup_printf("%f", tpp);
        gchar *ppg_str = g_strdup_printf("%f", ppg);
        gchar *spg_str = g_strdup_printf("%f", spg);

        // 打開add的視窗
        add_win = create_addwin();

        // 輸入數據
        gtk_entry_set_text(GTK_ENTRY(entry_name), name);
        gtk_entry_set_text(GTK_ENTRY(entry_gp), gp_str);
        gtk_entry_set_text(GTK_ENTRY(entry_fpg), fpg_str);
        gtk_entry_set_text(GTK_ENTRY(entry_tpp), tpp_str);
        gtk_entry_set_text(GTK_ENTRY(entry_ppg), ppg_str);
        gtk_entry_set_text(GTK_ENTRY(entry_spg), spg_str);

        g_free(name);
        g_free(gp_str);
        g_free(fpg_str);
        g_free(tpp_str);
        g_free(ppg_str);
        g_free(spg_str);
    }
}

void add_data_from_file(gchar *filename) {
    GtkListStore *store;
    GtkTreeIter iter;
    GtkTreeModel *model;
    char *name;
    int gp;
    float fgp, tpp, ppg, spg;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    char *data = read_json_to_str(filename);
    cJSON *tmp_obj = cJSON_Parse(data);
    cJSON *new_players = cJSON_GetObjectItem(tmp_obj, "Players");
    int player_num = cJSON_GetArraySize(new_players);
    for (int i = 0; i < player_num; ++i) {
        cJSON *tmp = cJSON_GetArrayItem(new_players, i);
        name = cJSON_GetStringValue(cJSON_GetObjectItem(tmp, "Name"));
        gp = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "GP"));
        fgp = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "FG"));
        tpp = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "3P"));
        ppg = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "PPG"));
        spg = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "SPG"));
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, LIST_TEAM, find_team, LIST_NAME, name, LIST_GP, gp, LIST_FPG, fgp, LIST_PPG, ppg, LIST_SPG, spg, LIST_TPP, tpp, -1);
        insert_data_to_data_base(name, gp, fgp, ppg, spg, tpp);
    }
}

void on_file_selected(GtkFileChooserButton *filechooser, gpointer data) {
    gchar *filepath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooser));
    gchar *filename = g_path_get_basename(filepath);
    add_data_from_file(filename);
    // g_print("Selected file: %s\n", filename);
    g_free(filepath);
}

void file_select_win(GtkWidget *widget, gpointer data) {
    GtkWidget *vbox;
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "INPUT FILE DATA");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 40);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

    GtkWidget *filechooser = gtk_file_chooser_button_new("Select File", GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_box_pack_start(GTK_BOX(vbox), filechooser, FALSE, FALSE, 2);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    g_signal_connect(filechooser, "file-set", G_CALLBACK(on_file_selected), NULL);
    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(gtk_widget_destroy), window);

    gtk_widget_show_all(window);
}

// 測試column可不可以點擊
void column_clicked(GtkTreeViewColumn *column, gpointer data) {
    if (GPOINTER_TO_INT(data) == 0) {
        delete_table_item();
        printInorder(root);
    } else {
        Mergesort(&head, GPOINTER_TO_INT(data));
        delete_table_item();
        insert_AVL_to_gtk();
    }
}

void init_list(GtkWidget *list) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column, *column0, *column1, *column2, *column3, *column4, *column5;
    GtkListStore *store;
    gint sort_by[] = {0, 1, 2, 3, 4, 5};

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Team", renderer, "text", LIST_TEAM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    renderer = gtk_cell_renderer_text_new();
    column0 = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", LIST_NAME, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column0);
    gtk_tree_view_column_set_clickable(column0, TRUE);

    renderer = gtk_cell_renderer_text_new();
    column1 = gtk_tree_view_column_new_with_attributes("GP", renderer, "text", LIST_GP, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column1);
    gtk_tree_view_column_set_clickable(column1, TRUE);

    renderer = gtk_cell_renderer_text_new();
    column2 = gtk_tree_view_column_new_with_attributes("FG%", renderer, "text", LIST_FPG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column2);
    gtk_tree_view_column_set_clickable(column2, TRUE);

    renderer = gtk_cell_renderer_text_new();
    column3 = gtk_tree_view_column_new_with_attributes("3P%", renderer, "text", LIST_TPP, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column3);
    gtk_tree_view_column_set_clickable(column3, TRUE);

    renderer = gtk_cell_renderer_text_new();
    column4 = gtk_tree_view_column_new_with_attributes("PPG", renderer, "text", LIST_PPG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column4);
    gtk_tree_view_column_set_clickable(column4, TRUE);

    renderer = gtk_cell_renderer_text_new();
    column5 = gtk_tree_view_column_new_with_attributes("SPG", renderer, "text", LIST_SPG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column5);
    gtk_tree_view_column_set_clickable(column5, TRUE);

    store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_FLOAT, G_TYPE_FLOAT, G_TYPE_FLOAT, G_TYPE_FLOAT);

    gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

    if (not_init) {
        g_signal_connect(column0, "clicked", G_CALLBACK(column_clicked), GINT_TO_POINTER(sort_by[0]));
        g_signal_connect(column1, "clicked", G_CALLBACK(column_clicked), GINT_TO_POINTER(sort_by[1]));
        g_signal_connect(column2, "clicked", G_CALLBACK(column_clicked), GINT_TO_POINTER(sort_by[2]));
        g_signal_connect(column3, "clicked", G_CALLBACK(column_clicked), GINT_TO_POINTER(sort_by[3]));
        g_signal_connect(column4, "clicked", G_CALLBACK(column_clicked), GINT_TO_POINTER(sort_by[4]));
        g_signal_connect(column5, "clicked", G_CALLBACK(column_clicked), GINT_TO_POINTER(sort_by[5]));
        insert_json_to_AVL(find_team);
        insert_AVL_to_gtk();
        not_init = 0;
    }

    g_object_unref(store);
}

void traverse_all_to_tree(GtkWidget *tree_view) {
    GtkListStore *store;
    GtkTreeIter iter;
    GtkTreeModel *model;
    char *name;
    int time, gp;
    float fgp, tpp, ppg, spg;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));

    cJSON *Basket_Ball_Teams = cJSON_GetObjectItem(teams_data, "Basket_Ball_Teams");
    int size = cJSON_GetArraySize(Basket_Ball_Teams);
    // find team
    for (int i = 0; i < size; i++) {
        cJSON *team = cJSON_GetArrayItem(Basket_Ball_Teams, i);
        char *getTeamName = cJSON_GetStringValue(cJSON_GetObjectItem(team, "Team Name"));
        cJSON *tmp_team = cJSON_GetObjectItem(team, "Players");
        int teamSize = cJSON_GetArraySize(tmp_team);
        for (int i = 0; i < teamSize; ++i) {
            cJSON *tmp = cJSON_GetArrayItem(tmp_team, i);
            name = cJSON_GetStringValue(cJSON_GetObjectItem(tmp, "Name"));
            gp = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "GP"));
            fgp = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "FG"));
            tpp = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "3P"));
            ppg = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "PPG"));
            spg = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "SPG"));
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, LIST_TEAM, getTeamName, LIST_NAME, name, LIST_GP, gp, LIST_FPG, fgp, LIST_PPG, ppg, LIST_SPG, spg, LIST_TPP, tpp, -1);
        }
    }
}

void traverse_win(GtkWidget *widget, gpointer data) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);  // 創建可滾動的視窗

    gtk_window_set_title(GTK_WINDOW(window), "Traverse");  // 標題
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *tree_view = gtk_tree_view_new();
    init_list(tree_view);

    traverse_all_to_tree(tree_view);

    // 設置滾動窗口的滾動策略為自動
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    gtk_widget_show_all(window);
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

void create_after_window(gchar *username) {
    GtkWidget *sw, *remove, *add, *edit, *io, *traverse, *vbox, *hbox, *searchEntry;
    find_team = username;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Player Data");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 600, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

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

    init_list(list);

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

    g_signal_connect(G_OBJECT(searchEntry), "activate", G_CALLBACK(on_search_activate), list);
    g_signal_connect(G_OBJECT(add), "clicked", G_CALLBACK(append_item), NULL);
    g_signal_connect(G_OBJECT(remove), "clicked", G_CALLBACK(remove_item), NULL);
    g_signal_connect(G_OBJECT(edit), "clicked", G_CALLBACK(edit_item), selection);
    g_signal_connect(G_OBJECT(io), "clicked", G_CALLBACK(file_select_win), NULL);
    g_signal_connect(G_OBJECT(traverse), "clicked", G_CALLBACK(traverse_win), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(list, "row-activated", G_CALLBACK(double_click_row), selection);

    gtk_widget_show_all(window);

    gtk_main();
}
