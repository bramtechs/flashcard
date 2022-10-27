#pragma once

#include <gtkmm.h>
#include "SessionWindow.hpp"

struct CsvEntryLine {
    Gtk::Entry word;
    Gtk::Entry definition;
};

class CsvGrid : public Gtk::Grid {
public:
    CsvGrid(Gtk::Grid::BaseObjectType* obj, Glib::RefPtr<Gtk::Builder>& builder);
    void resetRows();
    void openRows();
    void exportRows();
    void exportAsRows();
    void addNewRow();
    void pruneRows();
    void importRows();
    void startSession();
private:
    std::string currentFile;
    std::vector<CsvEntryLine> lines;
    Gtk::FileChooserDialog *chooser;

    Glib::RefPtr<Gtk::Builder> builder;

    void import_responded(int response = GTK_RESPONSE_OK);
    void export_responded(int response = GTK_RESPONSE_OK);
};