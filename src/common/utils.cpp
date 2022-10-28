#include <fstream>
#include <string>
#include <gtkmm.h>

#include "utils.hpp"
#include "logger.hpp"

bool utils::file_exists(const std::string &path) {
    std::ifstream file = std::ifstream(path.c_str());
    return file.good();
}

bool utils::try_add_glade_file(Glib::RefPtr<Gtk::Builder> &builder, const std::string &path) {
    try {
        builder->add_from_file(path);
        return true;
    }
    catch (const Glib::FileError &ex) {
        // This was your case, because the Application.glade file could
        // not be located:
        logger::error("File error : " + ex.what());
    }
    catch (const Glib::MarkupError &ex) {
        logger::error("Markup error : " + ex.what());
    }
    catch (const Gtk::BuilderError &ex) {
        logger::error("Builder error : " + ex.what());
    }
    return false;
}

std::string utils::read_file_as_string(const std::string &fileName) {
    std::string line;
    std::string content;
    std::ifstream file(fileName);
    if (file.is_open()) {
        while (getline(file, line)) {
            content += line + '\n';
        }
        file.close();
    } else {
        logger::error("Unable to open file " + fileName);
    }

    return content;
}

bool utils::write_string_to_file(const std::string &filename, const std::string &content) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
        return true;
    }
    logger::error("Unable to write to file " + filename);
    return false;
}

std::vector<parser::ParsedCsvRecord> utils::parse_gtk_entries(std::vector<structs::CsvEntryLine>& lines) {
    std::vector<parser::ParsedCsvRecord> records;
    auto line = std::begin(lines);
    while (line != std::end(lines)) {
        auto word = &line->word;
        auto def = &line->definition;
        records.push_back({
                                  .word = word->get_text(),
                                  .definition = def->get_text(),
                          });
        ++line;
    }
    return records;
}