
#include "MainWindow.hpp"
#include <iostream>

MainWindow::MainWindow(Gtk::ApplicationWindow::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::ApplicationWindow(obj) {

    // get the grid and cast to CsvGrid
    builder->get_widget_derived("CellGrid", csvGrid);

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

    Gtk::Button *startButton = nullptr;
    builder->get_widget("StartButton", startButton);
    startButton->signal_clicked().connect(sigc::mem_fun(*csvGrid, &CsvGrid::startSession));

    // menubar
    Gtk::ImageMenuItem *quitMenuButton = nullptr;
    builder->get_widget("MenuFileQuit", quitMenuButton);
    quitMenuButton->signal_activate().connect(sigc::mem_fun(*this,&MainWindow::close));

    Gtk::ImageMenuItem *newMenuButton = nullptr;
    builder->get_widget("MenuFileNew", newMenuButton);
    newMenuButton->signal_activate().connect(sigc::mem_fun(*csvGrid,&CsvGrid::resetRows));

    Gtk::ImageMenuItem *openMenuButton = nullptr;
    builder->get_widget("MenuFileOpen", openMenuButton);
    openMenuButton->signal_activate().connect(sigc::mem_fun(*csvGrid,&CsvGrid::openRows));

    Gtk::ImageMenuItem *saveMenuButton = nullptr;
    builder->get_widget("MenuFileSave", saveMenuButton);
    saveMenuButton->signal_activate().connect(sigc::mem_fun(*csvGrid,&CsvGrid::exportRows));

    Gtk::ImageMenuItem *saveAsMenuButton = nullptr;
    builder->get_widget("MenuFileSaveAs", saveAsMenuButton);
    saveAsMenuButton->signal_activate().connect(sigc::mem_fun(*csvGrid,&CsvGrid::exportAsRows));
}