#pragma once

#include <gtkmm.h>

struct CsvEntryLine {
    Gtk::Entry word;
    Gtk::Entry definition;
};

class CsvGrid : public Gtk::Grid {
public:
    CsvGrid(Gtk::Grid::BaseObjectType* obj, const Glib::RefPtr<Gtk::Builder>& builder);
    void addNewRow();
    void pruneRows();
private:
    std::vector<CsvEntryLine> lines;
};