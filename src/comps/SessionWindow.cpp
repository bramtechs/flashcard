
#include "SessionWindow.hpp"
#include "../common.hpp"

SessionWindow::SessionWindow(Gtk::ApplicationWindow::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::ApplicationWindow(obj) {
    // FIXME try to merge init with constructor if possible

    // setup timer label
    timerLabel = nullptr;
    builder->get_widget("SessionTimer", timerLabel);
    timerLabelOriginalText = timerLabel->get_text();

    // collect components
    builder->get_widget("SessionWord", wordLabel);
    builder->get_widget("SessionDefinition", definitionLabel);
    builder->get_widget("SessionSwitch", sessionSwitch);

    builder->get_widget("SessionNext", nextButton);
    builder->get_widget("SessionPrevious", prevButton);
    builder->get_widget("SessionProgress", sessionProgress);

    builder->get_widget("SessionGood", goodButton);
    builder->get_widget("SessionBad", badButton);

    // link components
    sessionSwitch->property_active().signal_changed().connect(sigc::mem_fun(*this, &SessionWindow::toggleAnswer));
    nextButton->signal_clicked().connect(sigc::mem_fun(*this, &SessionWindow::nextWord));
    prevButton->signal_clicked().connect(sigc::mem_fun(*this, &SessionWindow::previousWord));

    goodButton->signal_clicked().connect(sigc::mem_fun(*this, &SessionWindow::goodWord));
    badButton->signal_clicked().connect(sigc::mem_fun(*this, &SessionWindow::badWord));

    auto con = Glib::signal_timeout().connect_seconds(sigc::mem_fun(*this,
                                                                    &SessionWindow::onMinuteTick),
                                                      60);
}

void SessionWindow::init(structs::Session &ses) {
    session = ses;
    minutesPassed = 0;
    currentIndex = 0;
    answerVisible = false;
    refresh();
    hardWords.clear();
    logger::log("Initialized new session!");
}

bool SessionWindow::onMinuteTick() {
    logger::log("minute passed");
    minutesPassed++;
    refresh();
    return true;
}

void SessionWindow::nextWord() {
    currentIndex++;
    if (currentIndex >= session.records.size()) {
        finish();
    } else {
        answerVisible = false;
        sessionSwitch->set_state(false);
        refresh();
    }
}

void SessionWindow::previousWord() {
    if (currentIndex > 0) {
        currentIndex--;
    }
    sessionSwitch->set_state(false);
    refresh();
}

void SessionWindow::goodWord() {
    session.records.erase(session.records.begin() + currentIndex);
    logger::log("Removed word from session");
    refresh();
    if (currentIndex >= session.records.size()) {
        finish();
    }
}

void SessionWindow::badWord() {
    parser::ParsedCsvRecord *entry = &session.records.at(currentIndex);
    hardWords.push_back(*entry);
    logger::log("Logged hard word to buffer");

    goodWord();
}

void SessionWindow::toggleAnswer() {
    answerVisible = sessionSwitch->get_state();
    refresh();
}

void SessionWindow::refresh() {
    parser::ParsedCsvRecord *entry = &session.records.at(currentIndex);

    // update word and definition
    wordLabel->set_text(entry->word);
    if (answerVisible) {
        definitionLabel->set_text(entry->definition);
    } else {
        definitionLabel->set_text("???");
    }

    // progress
    const std::string progressText = std::to_string(currentIndex + 1) + " / " + std::to_string(session.records.size());
    sessionProgress->set_text(progressText);
    double frac = (currentIndex + 1) / (double) session.records.size();
    sessionProgress->set_fraction(frac);

    // update clock
    std::string clockText = timerLabelOriginalText + std::to_string(minutesPassed) + " min";
    timerLabel->set_text(clockText);
}

void SessionWindow::finish() {
    logger::log("Finished!");
    hide();
    currentIndex = 0;
}