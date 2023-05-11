#include <stdio.h>
#include <gtk/gtk.h>

int main(int argc, char *argv[]){
	gtk_init(&argc, &argv);

	GtkWidget *window;
	GtkWidget *fixed;
	GtkWidget *entry1;
	GtkWidget *entry2;
	GtkWidget *button1;
	GtkWidget *title;
	GtkWidget *subtitle;
	PangoAttrList *attr_list;
    PangoAttribute *attr;

	//創視窗
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);//大小

	//放置widget的地方
    fixed = gtk_fixed_new();

	//輸入帳號密碼
	entry1 = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Username"); //框框內顯示文字
	entry2 = gtk_entry_new();	
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Password");
	gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);//如果要輸入東西 上面的文字會關掉

	//登入按鈕
    button1 = gtk_button_new_with_label("SIGN IN");
    gtk_widget_set_size_request(button1, 165, 20);

	//印出標題
	title = gtk_label_new("PLAYER DATA");
	attr_list = pango_attr_list_new();
    attr = pango_attr_foreground_new(65535, 32768, 0);//設定顏色
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(title), attr_list);//讓title轉換成橘色
	attr = pango_attr_weight_new(PANGO_WEIGHT_BOLD);//設定粗體
    pango_attr_list_insert(attr_list, attr);
    attr = pango_attr_size_new(24 * PANGO_SCALE);//設定大小
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(title), attr_list);
    pango_attr_list_unref(attr_list);

	//印出副標題
	subtitle = gtk_label_new("SIGN IN");
	attr_list = pango_attr_list_new();
	attr = pango_attr_weight_new(PANGO_WEIGHT_BOLD);//設定粗體
    pango_attr_list_insert(attr_list, attr);
    attr = pango_attr_size_new(18 * PANGO_SCALE);//設定大小
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(subtitle), attr_list);
    pango_attr_list_unref(attr_list);

	//widget的位置
    gtk_fixed_put(GTK_FIXED(fixed), button1, 100, 270);
	gtk_fixed_put(GTK_FIXED(fixed), entry1, 100, 150);
	gtk_fixed_put(GTK_FIXED(fixed), entry2, 100, 200);
	gtk_fixed_put(GTK_FIXED(fixed), title, 100, 50);
	gtk_fixed_put(GTK_FIXED(fixed), subtitle, 125, 100);
	
	//印出title
	gtk_widget_show(title);
	gtk_widget_show(subtitle);
	//關掉視窗的時候會break
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	//顯示視窗內所有widget
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show_all(window);

    gtk_main();
		
	
	return 0;
}
