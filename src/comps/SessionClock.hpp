#pragma once

#include <gtkmm.h>

class SessionClock : public Gtk::Label {

public:
    SessionClock(Gtk::Label::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder>& builder);
    void reset();
    bool onTick();
private:
    int minutesPassed;
    std::string original;
    std::string format();
};