
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
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
        std::cout << "File error :" << ex.what() << std::endl;
    }
    catch (const Glib::MarkupError &ex) {
        std::cout << "Markup error :" << ex.what() << std::endl;
    }
    catch (const Gtk::BuilderError &ex) {
        std::cout << "Builder error :" << ex.what() << std::endl;
    }
    return false;
}

Gtk::FileChooserDialog *utils::allocate_open_csv_dialog() {
    auto chooser = new Gtk::FileChooserDialog("Choose a csv file", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN,
                                              Gtk::DIALOG_MODAL);


    //Add response buttons to the dialog:
    chooser->add_button("_Cancel", Gtk::ResponseType::RESPONSE_CANCEL);
    chooser->add_button("_Open", Gtk::ResponseType::RESPONSE_OK);

    auto filter_csv = Gtk::FileFilter::create();
    filter_csv->set_name("csv/Comma Seperated Values");
    filter_csv->add_mime_type("text/x-csv");
    chooser->add_filter(filter_csv);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    chooser->add_filter(filter_any);

    return chooser;
}

std::string utils::read_file_as_string(const std::string& fileName) {
    std::string line;
    std::string content;
    std::ifstream file(fileName);
    if (file.is_open()) {
        while (getline(file, line)) {
            content += line + '\n';
        }
        file.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    return content;
}
