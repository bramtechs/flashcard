#include <iostream>
#include <gtkmm.h>
#include "comps/MainWindow.hpp"
#include "common.hpp"

constexpr const char* GLADE_FILE_PATH = "assets/application.glade";

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    auto builder = Gtk::Builder::create();

    if (!utils::try_add_glade_file(builder,GLADE_FILE_PATH)){
        auto parent = "../"+std::string(GLADE_FILE_PATH);
        utils::try_add_glade_file(builder,parent);
    }

    MainWindow *window = nullptr;
    builder->get_widget_derived("MainWindow", window);

    auto mainApp = app->run(*window);

    delete window;

    return 0;
}
