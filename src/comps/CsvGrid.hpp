#pragma once

#include <gtkmm.h>

struct CsvEntryLine {
    Gtk::Entry word;
    Gtk::Entry definition;
};

class CsvGrid : public Gtk::Grid {
public:
    CsvGrid(Gtk::Grid::BaseObjectType* obj, const Glib::RefPtr<Gtk::Builder>& builder);
    void resetRows();
    void openRows();
    void exportRows();
    void exportAsRows();
    void addNewRow();
    void pruneRows();
    void importRows();
private:
    std::string currentFile;
    std::vector<CsvEntryLine> lines;
    Gtk::FileChooserDialog *chooser;
    void import_responded(int response = GTK_RESPONSE_OK);
    void export_responded(int response = GTK_RESPONSE_OK);
};