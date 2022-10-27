
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <assert.h>
#include <gtkmm.h>

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
        utils::error("File error : " + ex.what());
    }
    catch (const Glib::MarkupError &ex) {
        utils::error("Markup error : " + ex.what());
    }
    catch (const Gtk::BuilderError &ex) {
        utils::error("Builder error : " + ex.what());
    }
    return false;
}

void add_filters_to_dialog(Gtk::FileChooserDialog *dialog) {
    auto filter_csv = Gtk::FileFilter::create();
    filter_csv->set_name("csv/Comma Seperated Values");
    filter_csv->add_mime_type("text/x-csv");
    dialog->add_filter(filter_csv);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);
}

Gtk::FileChooserDialog *utils::allocate_open_csv_dialog() {
    auto chooser = new Gtk::FileChooserDialog("Choose a csv file", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN,
                                              Gtk::DIALOG_MODAL);
    add_filters_to_dialog(chooser);

    //Add response buttons to the dialog:
    chooser->add_button("_Cancel", Gtk::ResponseType::RESPONSE_CANCEL);
    chooser->add_button("_Open", Gtk::ResponseType::RESPONSE_OK);
    return chooser;
}

Gtk::FileChooserDialog *utils::allocate_save_csv_dialog() {
    auto chooser = new Gtk::FileChooserDialog("Choose destination", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE,
                                              Gtk::DIALOG_MODAL);

    //Add response buttons to the dialog:
    chooser->add_button("_Cancel", Gtk::ResponseType::RESPONSE_CANCEL);
    chooser->add_button("_Save", Gtk::ResponseType::RESPONSE_YES);

    add_filters_to_dialog(chooser);
    return chooser;
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
        utils::error("Unable to open file " + fileName);
    }

    return content;
}

bool utils::write_string_to_file(const std::string &filename, const std::string& content) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
        return true;
    }
    utils::error("Unable to write to file " + filename);
    return false;
}

void utils::log(const std::string &text) {
    std::cout << "[INFO]: " << text << std::endl;
}

void utils::warn(const std::string &text) {
    std::cout << "[WARN]: " << text << std::endl;
}

void utils::error(const std::string &text) {
    std::cout << "[ERROR]: " << text << std::endl;
}

void utils::logAssert(const std::string &text, bool condition) {
    if (!condition) {
        error(text);
    }
    assert(condition);
}
