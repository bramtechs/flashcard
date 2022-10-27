
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
    utils::log("Pruned empty lines");
}

void CsvGrid::resetRows() {
    auto line = std::begin(lines);
    while (line != std::end(lines)) {
        auto word = &line->word;
        auto def = &line->definition;
        remove(*word);
        remove(*def);
        line = lines.erase(line);
    }
}

void CsvGrid::import_responded(int response) {
    if (response == GTK_RESPONSE_OK || response == GTK_RESPONSE_YES) {
        std::string filepath = chooser->get_filename();

        utils::log("Importing from " + filepath);
        std::string content = utils::read_file_as_string(filepath);
        std::vector<parser::ParsedCsvRecord> records = parser::string_to_records(content);

        unsigned int startRow = lines.size();
        for (const parser::ParsedCsvRecord &record: records) {
            addNewRow();
            CsvEntryLine *line = &lines[lines.size() - 1];
            line->word.set_text(record.word);
            line->definition.set_text(record.definition);
        }
    }else{
        utils::warn("Gave unexpected response " + std::to_string(response));
    }
    delete chooser;
    chooser = nullptr;
}

void CsvGrid::openRows() {
    resetRows();
    importRows();
}

void CsvGrid::export_responded(int response) {
    if (response == GTK_RESPONSE_OK || response == GTK_RESPONSE_YES) {
        std::string filepath;
        if (chooser == nullptr){
            filepath = currentFile;
        }else{
            filepath = chooser->get_filename();
        }
        currentFile = filepath;

        utils::log("Exporting to " + filepath);
    }else{
        utils::warn("Gave unexpected response " + std::to_string(response));
    }
    delete chooser;
    chooser = nullptr;
}

void CsvGrid::exportRows() {
    if (!currentFile.empty()) {
        utils::log("Saving to open file " +  currentFile);
        export_responded(GTK_RESPONSE_OK);
    } else {
        utils::log("Saving as new file " +  currentFile);
        exportAsRows();
    }
}

void CsvGrid::exportAsRows() {
    chooser = utils::allocate_save_csv_dialog();
    chooser->signal_response().connect(sigc::mem_fun(*this, &CsvGrid::export_responded));
    chooser->show();
}

void CsvGrid::importRows() {
    chooser = utils::allocate_open_csv_dialog();
    // on picker responded
    chooser->signal_response().connect(sigc::mem_fun(*this, &CsvGrid::import_responded));

    chooser->show();
}