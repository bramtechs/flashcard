#pragma once
#include <iostream>
#include <gtkmm.h>
#include "parser.hpp"

namespace structs {
   struct Session {
        std::vector<parser::ParsedCsvRecord> records;
   };
    struct CsvEntryLine {
        Gtk::Entry word;
        Gtk::Entry definition;
    };
}