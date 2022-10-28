#pragma once
#include <gtkmm.h>
#include "../common.hpp"

class SessionWindow : public Gtk::ApplicationWindow {
public:
    SessionWindow(Gtk::ApplicationWindow::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder>& builder);
    void init(structs::Session& ses);
private:
    structs::Session session;
};
