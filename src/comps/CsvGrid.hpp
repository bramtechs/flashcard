#pragma once

#include <gtkmm.h>
#include "../common.hpp"

class CsvGrid : public Gtk::Grid {
public:
    CsvGrid(Gtk::Grid::BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> &builder);

    void resetRows();

    void openRows();

    void exportRows();

    void exportAsRows();

    void addNewRow();

    void pruneRows();

    void importRows();

    void startSession();

    bool hasRows();

private:
    std::string currentFile;
    std::vector<structs::CsvEntryLine> lines;
    Gtk::FileChooserDialog *chooser;

    Glib::RefPtr<Gtk::Builder> builder;


    void import_responded(int response = GTK_RESPONSE_OK);

    void export_responded(int response = GTK_RESPONSE_OK);
};