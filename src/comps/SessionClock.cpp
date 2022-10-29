
#include "SessionClock.hpp"
#include "../common.hpp"

SessionClock::SessionClock(Gtk::Label::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Label(obj) {
    original = get_text();
    auto con = Glib::signal_timeout().connect_seconds(sigc::mem_fun(*this,
                                                                    &SessionClock::onTick),
                                                      60);
    reset();
}

void SessionClock::reset() {
    minutesPassed = 0;
    set_text(format());
    logger::log("Clock reset");
}

bool SessionClock::onTick() {
    logger::log("minute passed");
    minutesPassed++;
    set_text(format());
    return true;
}

std::string SessionClock::format() {
    return original + std::to_string(minutesPassed) + " min";
}