#include "ToolbarOptions.h"

//void Wicher::ToolbarOptions::on_ok_click(){
//    window->hide();
//}

Wicher::ToolbarOptions::ToolbarOptions(Glib::RefPtr<Gtk::Window> parent) : parent(parent) {
    Toolkit::log("Preparing Info window... (net.majudev.wicher.gtk.main)");
    builder = Wicher::Builder::getSingleton().getBuilder();

    builder->get_widget("options_window", window);
    //builder->get_widget("options_window_ok_button", ok_button);
    if(window){
        Wicher::Toolkit::set_icon(window);
        //if(ok_button){
        //    ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::ToolbarInfo::on_ok_click) );
        //}
    }
}

void Wicher::ToolbarOptions::show(){
    window->show_all();
}
