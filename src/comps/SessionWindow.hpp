#pragma once
#include <gtkmm.h>
#include "../common.hpp"
#include "SessionClock.hpp"

class SessionWindow : public Gtk::ApplicationWindow {
public:
    SessionWindow(Gtk::ApplicationWindow::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder>& builder);
    void init(structs::Session& ses);
private:
    structs::Session session;

    int currentIndex;
    bool answerVisible;

    // components
    Gtk::Label *wordLabel;
    Gtk::Label *definitionLabel;
    Gtk::Switch *sessionSwitch;
    Gtk::Button *nextButton;
    Gtk::Button *prevButton;
    Gtk::Button *goodButton;
    Gtk::Button *badButton;
    Gtk::Button *exportButton;

    Gtk::ProgressBar *sessionProgress;
    Gtk::FileChooserDialog *exportDialog;
    SessionClock *clock;

    std::vector<parser::ParsedCsvRecord> hardWords;

    void refresh();
    void nextWord();
    void previousWord();
    void goodWord();
    void badWord();
    void toggleAnswer();

    void exportHard();
    void exportResponded(int response);
};
