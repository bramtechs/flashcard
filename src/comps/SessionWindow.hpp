#pragma once
#include <gtkmm.h>

class SessionWindow : public Gtk::ApplicationWindow {
public:
    SessionWindow(Gtk::ApplicationWindow::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder>& builder);
};
