#include "SignalWindows.h"

void Wicher::SignalWindows::show_info_pz_window(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column){
    if(!is_shown_info_pz_window()){
        Gtk::TreeView * view = column->get_tree_view();
        Gtk::TreeModel::iterator iter = view->get_model()->get_iter(path);
        if(iter){
            Gtk::TreeModel::Row row = *iter;
            int id = row[pz_columns.id];
            int wz_id = row[pz_columns.id];
            Glib::ustring person = row[pz_columns.person];
            Glib::ustring date = row[pz_columns.date];
            Glib::ustring comment = row[pz_columns.comment];
            this->info_pz_id_entry->set_text(Wicher::Toolkit::itostr(id));
            this->info_pz_wz_id_entry->set_text(Wicher::Toolkit::itostr(wz_id));
            this->info_pz_date_entry->set_text(date);
            this->info_pz_person_entry->set_text(person);
            this->info_pz_comment_entry->set_text(comment);

            this->info_pz_items_list->clear();
            json_error_t error;
            json_t * root = json_loads(Wicher::Database::getSingleton().run(Wicher::Database::Query::get_wz_items(wz_id)).c_str(), 0, &error);
            if(!root){
                Wicher::Dialogger::response_error(info_pz_window, error);
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
                                    Gtk::TreeModel::iterator iterc = this->info_pz_items_list->append();
                                    Gtk::TreeModel::Row rowc = *iterc;
                                    rowc[wz_items_list_columns.id] = item_id;
                                    rowc[wz_items_list_columns.type] = item_type;
                                    rowc[wz_items_list_columns.type_name] = "";
                                }
                                ++x;
                            }
                        }
                    }else Wicher::Dialogger::query_error(info_wz_window, root);
                }
                free(root);
            }

            this->info_pz_window->show_all();
        }
    }else Dialogger::creating_already_shown(info_pz_window);
}

void Wicher::SignalWindows::on_info_pz_ok_button_clicked(){
        this->info_pz_window->close();
}

void Wicher::SignalWindows::on_info_pz_print_button_clicked(){
    Gtk::MessageDialog dialog(*this->info_pz_window, "Ta funkcja nie jest jeszcze aktywna!");
    dialog.set_secondary_text("Ta funkcja nie została jeszcze napisana.");
    dialog.run();
}

bool Wicher::SignalWindows::is_shown_info_pz_window(){
    return this->info_pz_window->is_visible();
}
