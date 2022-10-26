
#include <iostream>
#include <tuple>

#include "CsvGrid.hpp"
#include "../utils.hpp"
#include "../parser.hpp"

CsvGrid::CsvGrid(Gtk::Grid::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder> &builder) : Gtk::Grid(obj) {
}

void CsvGrid::addNewRow() {
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

void CsvGrid::import_responded(int response){
   std::string filepath = chooser->get_filename();
   delete chooser;

   std::cout << "Importing from " << filepath << std::endl;
   std::string content = utils::read_file_as_string(filepath);
   std::vector<parser::ParsedCsvRecord> records = parser::string_to_records(content);

   unsigned int startRow = lines.size();
   for (parser::ParsedCsvRecord record : records){
        addNewRow();
        CsvEntryLine *line = &lines[lines.size() - 1];
        line->word.set_text(record.word);
        line->definition.set_text(record.definition);
   }
}

void CsvGrid::importRows() {
    chooser = utils::allocate_open_csv_dialog();
    // on picker responded
    chooser->signal_response().connect(sigc::mem_fun(*this,&CsvGrid::import_responded));

    chooser->show();
}