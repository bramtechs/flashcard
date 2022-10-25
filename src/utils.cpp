
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