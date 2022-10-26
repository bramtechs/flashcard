#pragma once

#include <iostream>
#include <gtkmm.h>

namespace utils {
    bool file_exists(const std::string& path);
    std::string read_file_as_string(const std::string& fileName);

    bool try_add_glade_file(Glib::RefPtr<Gtk::Builder>& builder, const std::string& path);
    Gtk::FileChooserDialog* allocate_open_csv_dialog();
}