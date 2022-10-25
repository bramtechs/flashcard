
#include "CsvGrid.hpp"
#include <iostream>
#include <tuple>

CsvGrid::CsvGrid(Gtk::Grid::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder> &builder) : Gtk::Grid(obj) {
}

void CsvGrid::addNewRow() {
    std::cout << get_name() << std::endl;

    //Gtk::Entry entry = Gtk::Entry();
    //entry.set_text("Hello");

    lines.emplace_back();

    CsvEntryLine *line = &lines[lines.size() - 1];

    int y = (int) lines.size();
    attach(line->word, 0, y);
    attach(line->definition, 1, y);

    show_all();
}

void CsvGrid::pruneRows() {
    // remove empty lines
    auto line = std::begin(lines);
    while (line != std::end(lines)) {
        auto word = &line->word;
        auto def = &line->definition;
        if (word->get_text().empty() && def->get_text().empty()) {
            remove(*word);
            remove(*def);
            line = lines.erase(line);
        } else {
            ++line;
        }
    }
    std::cout << "Pruned empty lines" << std::endl;
}
