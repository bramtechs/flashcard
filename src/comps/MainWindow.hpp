#pragma once

#include <gtkmm.h>
#include "CsvGrid.hpp"

class MainWindow : public Gtk::ApplicationWindow {
public:
    MainWindow(Gtk::ApplicationWindow::BaseObjectType* obj, const Glib::RefPtr<Gtk::Builder>& builder);
private:
    CsvGrid *csvGrid;
};

