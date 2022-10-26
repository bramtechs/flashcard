#pragma once

#include <iostream>
#include <gtkmm.h>

namespace utils {
    bool file_exists(const std::string& path);

    bool try_add_glade_file(Glib::RefPtr<Gtk::Builder>& builder, const std::string& path);

    Gtk::FileChooserDialog* allocateCsvOpenDialog(void (*callback)(const std::string&));
}