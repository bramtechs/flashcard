#pragma once

#include <iostream>
#include <gtkmm.h>
#include "structs.hpp"

namespace utils {
    bool file_exists(const std::string &path);

    std::string read_file_as_string(const std::string &fileName);

    bool write_string_to_file(const std::string &filename, const std::string &content);

    bool try_add_glade_file(Glib::RefPtr<Gtk::Builder> &builder, const std::string &path);

    std::vector<parser::ParsedCsvRecord> parse_gtk_entries(std::vector<structs::CsvEntryLine>& lines);
}