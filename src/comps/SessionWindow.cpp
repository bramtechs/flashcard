
#include "SessionWindow.hpp"
#include "../common.hpp"

SessionWindow::SessionWindow(Gtk::ApplicationWindow::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::ApplicationWindow(obj) {

}

void SessionWindow::init(structs::Session &ses) {
    session = ses;
    logger::log("Initialized new ses!");
}
