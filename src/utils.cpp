
#include "utils.hpp"
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

Gtk::FileChooserDialog *utils::allocateCsvOpenDialog(void (*callback)(const std::string&)) {
    auto chooser = new Gtk::FileChooserDialog("Choose a csv file", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN,
                                              Gtk::DIALOG_MODAL);

    // on picker responded
    chooser->signal_response().connect([=](int response) {
        switch (response) {
            case Gtk::ResponseType::RESPONSE_OK:
                callback(chooser->get_filename());
                break;
            case Gtk::ResponseType::RESPONSE_CANCEL:
                std::cout << "File picker canceled." << std::endl;
                break;
            default:
                std::cout << "Unexpected button clicked." << std::endl;
                break;
        }
        delete chooser;
        std::cout << "Disposed file picker." << std::endl;
    });

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
