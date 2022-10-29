
#include <iostream>
#include <random>

#include "CsvGrid.hpp"
#include "../common.hpp"
#include "SessionWindow.hpp"

CsvGrid::CsvGrid(Gtk::Grid::BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> &builder) : Gtk::Grid(obj) {
    this->builder = builder;
}

void CsvGrid::addNewRow() {
    lines.emplace_back();

    structs::CsvEntryLine *line = &lines[lines.size() - 1];

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
    logger::log("Pruned empty lines");
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
        auto filepaths = chooser->get_filenames();
        for (const auto& filepath: filepaths) {
            logger::log("Importing from " + filepath);
            std::string content = utils::read_file_as_string(filepath);
            std::vector<parser::ParsedCsvRecord> records = parser::string_to_records(content);

            unsigned int startRow = lines.size();
            for (const parser::ParsedCsvRecord &record: records) {
                addNewRow();
                structs::CsvEntryLine *line = &lines[lines.size() - 1];
                line->word.set_text(record.word);
                line->definition.set_text(record.definition);
            }
        }
    } else {
        logger::warn("Gave unexpected response " + std::to_string(response));
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
        if (chooser == nullptr) {
            filepath = currentFile;
        } else {
            filepath = chooser->get_filename();
        }
        currentFile = filepath;

        // prune rows before saving
        pruneRows();

        // parse gtk entry widgets
        auto records = utils::parse_gtk_entries(lines);

        std::string result = parser::records_to_string(records);
        utils::write_string_to_file(filepath, result);
        logger::log("Exported to " + filepath);
    } else {
        logger::warn("Gave unexpected response " + std::to_string(response));
    }
    delete chooser;
    chooser = nullptr;
}

void CsvGrid::exportRows() {

    if (!currentFile.empty()) {
        logger::log("Saving to open file " + currentFile);
        export_responded(GTK_RESPONSE_OK);
    } else {
        logger::log("Saving as new file " + currentFile);
        exportAsRows();
    }
}

void CsvGrid::exportAsRows() {
    chooser = picker::allocate_save_csv_dialog();
    chooser->signal_response().connect(sigc::mem_fun(*this, &CsvGrid::export_responded));
    chooser->show();
}

void CsvGrid::importRows() {
    chooser = picker::allocate_open_csv_dialog();
    // on picker responded
    chooser->signal_response().connect(sigc::mem_fun(*this, &CsvGrid::import_responded));

    chooser->show();
}

void CsvGrid::startSession() {
    pruneRows();
    if (hasRows()) {
        logger::log("Starting session!");
        SessionWindow *window = nullptr;
        builder->get_widget_derived("SessionWindow", window);

        // session
        auto records = utils::parse_gtk_entries(lines);
        std::shuffle(records.begin(), records.end(), std::mt19937(std::random_device()()));

        structs::Session session = {
                .records = records
        };

        window->init(session);
        window->show_all();
    } else {
        logger::warn("No rows defined!");
    }
}

bool CsvGrid::hasRows() {
    return !lines.empty();
}
