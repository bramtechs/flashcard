
#include "MainWindow.hpp"
#include <iostream>

MainWindow::MainWindow(Gtk::ApplicationWindow::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::ApplicationWindow(obj) {

    // get the grid and cast to CsvGrid
    builder->get_widget_derived("CellGrid",csvGrid);

    // linkSignals signals
    Gtk::Button *addRowButton = nullptr;
    builder->get_widget("AddRowButton", addRowButton);
    addRowButton->signal_clicked().connect(sigc::mem_fun(*csvGrid, &CsvGrid::addNewRow));

    Gtk::Button *pruneButton = nullptr;
    builder->get_widget("PruneButton", pruneButton);
    pruneButton->signal_clicked().connect(sigc::mem_fun(*csvGrid, &CsvGrid::pruneRows));

    Gtk::Button *importButton = nullptr;
    builder->get_widget("ImportButton", importButton);
    importButton->signal_clicked().connect(sigc::mem_fun(*csvGrid, &CsvGrid::importRows));
}