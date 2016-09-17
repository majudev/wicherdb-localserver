#ifndef TOOLBAROPTIONS_H
#define TOOLBAROPTIONS_H
#include <gtkmm.h>
#include <string>
#include "Toolkit.h"
#include "Builder.h"

namespace Wicher{
class ToolbarOptions{
    public:
        ToolbarOptions(Glib::RefPtr<Gtk::Window> parent);
        void show();

    private:
        Glib::RefPtr<Gtk::Builder> builder;
        Glib::RefPtr<Gtk::Window> parent;
        Gtk::Window * window;
};
}

#endif // SPLASH_H
