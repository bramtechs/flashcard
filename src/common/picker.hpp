#pragma once

#include "gtkmm.h"

namespace picker {
    Gtk::FileChooserDialog *allocate_open_csv_dialog();

    Gtk::FileChooserDialog *allocate_save_csv_dialog();
}