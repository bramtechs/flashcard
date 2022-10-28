#pragma once
#include <gtkmm.h>
#include "../common.hpp"

class SessionWindow : public Gtk::ApplicationWindow {
public:
    SessionWindow(Gtk::ApplicationWindow::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder>& builder);
    void init(structs::Session& ses);
private:
    structs::Session session;
    int minutesPassed;

    int currentIndex;
    bool answerVisible;

    // components
    Gtk::Label *wordLabel;
    Gtk::Label *definitionLabel;
    Gtk::Switch *sessionSwitch;
    Gtk::Button *nextButton;
    Gtk::Button *prevButton;
    Gtk::ProgressBar *sessionProgress;

    // TODO put in own class
    Gtk::Label* timerLabel;
    std::string timerLabelOriginalText;
    bool onMinuteTick();

    void refresh();
    void nextWord();
    void previousWord();
    void goodWord();
    void badWord();
    void toggleAnswer();
};
