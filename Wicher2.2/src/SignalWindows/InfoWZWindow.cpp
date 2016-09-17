#include "SignalWindows.h"

Wicher::WZItemsListColumns::WZItemsListColumns(){
    add(id); add(type); add(type_name);
}

void Wicher::SignalWindows::show_info_wz_window(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column){
    if(!is_shown_info_wz_window()){
        Gtk::TreeView * view = column->get_tree_view();
        Gtk::TreeModel::iterator iter = view->get_model()->get_iter(path);
        if(iter){
            Gtk::TreeModel::Row row = *iter;
            int id = row[wz_columns.id];
            Glib::ustring person = row[wz_columns.person];
            Glib::ustring date = row[wz_columns.date];
            Glib::ustring return_date = row[wz_columns.return_date];
            Glib::ustring comment = row[wz_columns.comment];
            this->info_wz_id_entry->set_text(Wicher::Toolkit::itostr(id));
            this->info_wz_date_entry->set_text(date);
            this->info_wz_person_entry->set_text(person);
            this->info_wz_comment_entry->set_text(comment);

            this->info_wz_items_list->clear();
            json_error_t error;
            json_t * root = json_loads(Wicher::Database::getSingleton().run(Wicher::Database::Query::get_wz_items(id)).c_str(), 0, &error);
            if(!root){
                Wicher::Dialogger::response_error(info_wz_window, error);
            }else{
                const char * response_str = json_string_value(json_object_get(root, "response"));
                if(response_str){
                    std::string response(response_str);
                    if(response == std::string("ok")){
                        json_t * array = json_object_get(root, "items");
                        if(array){
                            size_t size = json_array_size(array);
                            size_t x = 0;
                            while(x != size){
                                json_t * obj = json_array_get(array, x);
                                int item_id = json_integer_value(json_object_get(obj, "id"));
                                const char * item_type = json_string_value(json_object_get(obj, "type"));
                                if(item_type){
                                    Gtk::TreeModel::iterator iterc = this->info_wz_items_list->append();
                                    Gtk::TreeModel::Row rowc = *iterc;
                                    rowc[wz_items_list_columns.id] = item_id;
                                    rowc[wz_items_list_columns.type] = Glib::ustring(item_type);
                                }
                                ++x;
                            }
                        }
                    }else Wicher::Dialogger::query_error(info_wz_window, root);
                }
                free(root);
            }

            this->info_wz_window->show_all();

            if(Wicher::Toolkit::date_is_valid(return_date)){
                this->info_wz_return_date_entry->set_text(return_date);
                this->info_wz_return_date_box->show_all();
            }else{
                this->info_wz_return_date_box->hide();
            }
        }
    }else Dialogger::creating_already_shown(info_wz_window);
}

void Wicher::SignalWindows::on_info_wz_ok_button_clicked(){
        this->info_wz_window->close();
}

void Wicher::SignalWindows::on_info_wz_pz_button_clicked(){
    Glib::ustring id = this->info_wz_id_entry->get_text();
    if(this->info_wz_return_date_box->is_visible()){
        /*Gtk::MessageDialog dialog(*this->info_wz_window, "Ta funkcja nie jest jeszcze aktywna!");
        dialog.set_secondary_text("Ta funkcja nie została jeszcze napisana.");
        dialog.run();*/
        Gtk::TreeModel::Children children = this->pz_list->children();
        for(Gtk::TreeModel::Children::iterator iter = children.begin(); iter != children.end(); ++iter){
            Gtk::TreeModel::Row row = *iter;
            if(row[pz_columns.wz_id] == Wicher::Toolkit::strtoi(id)){
                this->show_info_pz_window(this->pz_list->get_path(iter), this->pz_tree->get_column(0));
            }
        }
        this->info_wz_window->close();
    }else{
        this->show_create_pz_window(Wicher::Toolkit::strtoi(id));
        this->info_wz_window->close();
    }
}

void Wicher::SignalWindows::on_info_wz_print_button_clicked(){
    Gtk::MessageDialog dialog(*this->info_wz_window, "Ta funkcja nie jest jeszcze aktywna!");
    dialog.set_secondary_text("Ta funkcja nie została jeszcze napisana.");
    dialog.run();
}

bool Wicher::SignalWindows::is_shown_info_wz_window(){
    return this->info_wz_window->is_visible();
}
