#pragma once

#include <gtkmm.h>
#include <iostream>
#include "CsvGrid.hpp"

class MainWindow : public Gtk::ApplicationWindow {
public:
    MainWindow(Gtk::ApplicationWindow::BaseObjectType* obj, const Glib::RefPtr<Gtk::Builder>& builder);
private:
    CsvGrid *csvGrid;
    void test(int response){
        std::cout << "worked" << std::endl;
    };
};

