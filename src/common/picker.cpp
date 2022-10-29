#include "picker.hpp"

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

Gtk::FileChooserDialog *picker::allocate_open_csv_dialog() {
    auto chooser = new Gtk::FileChooserDialog("Choose a csv file", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN,
                                              Gtk::DIALOG_MODAL);
    chooser->set_select_multiple(true);
    add_filters_to_dialog(chooser);

    //Add response buttons to the dialog:
    chooser->add_button("_Cancel", Gtk::ResponseType::RESPONSE_CANCEL);
    chooser->add_button("_Open", Gtk::ResponseType::RESPONSE_OK);
    return chooser;
}

Gtk::FileChooserDialog *picker::allocate_save_csv_dialog() {
    auto chooser = new Gtk::FileChooserDialog("Choose destination", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE,
                                              Gtk::DIALOG_MODAL);

    //Add response buttons to the dialog:
    chooser->add_button("_Cancel", Gtk::ResponseType::RESPONSE_CANCEL);
    chooser->add_button("_Save", Gtk::ResponseType::RESPONSE_YES);

    add_filters_to_dialog(chooser);
    return chooser;
}