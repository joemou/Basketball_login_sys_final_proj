#include <gtk/gtk.h>

enum
{
    LIST_NAME,
    LIST_GP,
    LIST_MPG,
    LIST_PPG,
    LIST_TP,
    LIST_FGM,
    LIST_FG,
    LIST_PM,
    LIST_TO,
    LIST_PF,
    N_COLUMNS
};

GtkWidget *list;
GtkWidget *add_win;
GtkWidget *entry_name;
GtkWidget *entry_gp;
GtkWidget *entry_mpg;
GtkWidget *entry_ppg;
GtkWidget *entry_tp;
GtkWidget *entry_fgm;
GtkWidget *entry_fg;
GtkWidget *entry_pm;
GtkWidget *entry_to;
GtkWidget *entry_pf;
GtkWidget *window;
GtkTreeSelection *selection;

void on_ok_clicked(GtkWidget *button, gpointer data)
{
    GtkListStore *store;
    GtkTreeIter iter;
    GtkTreeModel *model;

    const gchar *str1 = gtk_entry_get_text(GTK_ENTRY(entry_name));
    const gchar *str2 = gtk_entry_get_text(GTK_ENTRY(entry_gp));
    const gchar *str3 = gtk_entry_get_text(GTK_ENTRY(entry_mpg));
    const gchar *str4 = gtk_entry_get_text(GTK_ENTRY(entry_ppg));
    const gchar *str5 = gtk_entry_get_text(GTK_ENTRY(entry_tp));
    const gchar *str6 = gtk_entry_get_text(GTK_ENTRY(entry_fgm));
    const gchar *str7 = gtk_entry_get_text(GTK_ENTRY(entry_fg));
    const gchar *str8 = gtk_entry_get_text(GTK_ENTRY(entry_pm));
    const gchar *str9 = gtk_entry_get_text(GTK_ENTRY(entry_to));
    const gchar *str10 = gtk_entry_get_text(GTK_ENTRY(entry_pf));

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))
    {
        gtk_list_store_set(store, &iter, LIST_NAME, str1, LIST_GP, str2, LIST_MPG, str3, LIST_PPG, str4, LIST_TP, str5, LIST_FGM, str6, LIST_FG, str7, LIST_PM, str8, LIST_TO, str9, LIST_PF, str10, -1);
    }
    else
    {
        gtk_list_store_append(store, &iter); 
        gtk_list_store_set(store, &iter, LIST_NAME, str1, LIST_GP, str2, LIST_MPG, str3, LIST_PPG, str4, LIST_TP, str5, LIST_FGM, str6, LIST_FG, str7, LIST_PM, str8, LIST_TO, str9, LIST_PF, str10, -1);
    }


    gtk_widget_destroy(add_win);
}

void on_cancel_clicked(GtkWidget *button, gpointer data)
{
    gtk_widget_destroy(add_win);
}

GtkWidget *create_addwin()
{
    GtkWidget *win;
    GtkWidget *vbox;
    GtkWidget *grid;
    GtkWidget *hbox;
    GtkWidget *label;
    GtkWidget *button;

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
        gchar *gp;
        gchar *mpg;
        gchar *ppg;
        gchar *tp;
        gchar *fgm;
        gchar *fg;
        gchar *pm;
        gchar *to;
        gchar *pf;
        gtk_tree_model_get(model, &iter, LIST_NAME, &name, LIST_GP, &gp, LIST_MPG, &mpg, LIST_PPG, &ppg, LIST_TP, &tp, LIST_FGM, &fgm, LIST_FG, &fg, LIST_PM, &pm, LIST_TO, &to, LIST_PF, &pf, -1);

        add_win = create_addwin();
        gtk_entry_set_text(GTK_ENTRY(entry_name), name);
        gtk_entry_set_text(GTK_ENTRY(entry_gp), gp);
        gtk_entry_set_text(GTK_ENTRY(entry_mpg), mpg);
        gtk_entry_set_text(GTK_ENTRY(entry_ppg), ppg);
        gtk_entry_set_text(GTK_ENTRY(entry_tp), tp);
        gtk_entry_set_text(GTK_ENTRY(entry_fgm), fgm);
        gtk_entry_set_text(GTK_ENTRY(entry_fg), fg);
        gtk_entry_set_text(GTK_ENTRY(entry_pm), pm);
        gtk_entry_set_text(GTK_ENTRY(entry_to), to);
        gtk_entry_set_text(GTK_ENTRY(entry_pf), pf);

        g_free(name);
        g_free(gp);
        g_free(mpg);
        g_free(ppg);
        g_free(tp);
        g_free(fgm);
        g_free(fg);
        g_free(pm);
        g_free(to);
        g_free(pf);
    }
}

void init_list(GtkWidget *list)
{

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", LIST_NAME, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("GP", renderer, "text", LIST_GP, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("MPG", renderer, "text", LIST_MPG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("PPG", renderer, "text", LIST_PPG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("TP", renderer, "text", LIST_TP, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("FGM", renderer, "text", LIST_FGM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("FG%", renderer, "text", LIST_FG, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("3PM", renderer, "text", LIST_PM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("TO", renderer, "text", LIST_TO, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("PF", renderer, "text", LIST_PF, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

    g_object_unref(store);
}

int main(int argc, char *argv[])
{

    GtkWidget *sw;

    GtkWidget *remove;
    GtkWidget *add;
    GtkWidget *edit;

    GtkWidget *vbox;
    GtkWidget *hbox;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Player Data");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 370, 270);

    sw = gtk_scrolled_window_new(NULL, NULL);
    list = gtk_tree_view_new();
    gtk_container_add(GTK_CONTAINER(sw), list);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw), GTK_SHADOW_ETCHED_IN);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    gtk_box_pack_start(GTK_BOX(vbox), sw, TRUE, TRUE, 5);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    add = gtk_button_new_with_label("Add");
    remove = gtk_button_new_with_label("Remove");
    edit = gtk_button_new_with_label("Edit");

    gtk_box_pack_start(GTK_BOX(hbox), add, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), remove, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), edit, TRUE, TRUE, 3);

    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 3);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    init_list(list);

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

    g_signal_connect(G_OBJECT(add), "clicked", G_CALLBACK(append_item), NULL);
    g_signal_connect(G_OBJECT(remove), "clicked", G_CALLBACK(remove_item), selection);
    g_signal_connect(G_OBJECT(edit), "clicked", G_CALLBACK(edit_item), selection);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
