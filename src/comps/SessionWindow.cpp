
#include "SessionWindow.hpp"
#include "../common.hpp"

SessionWindow::SessionWindow(Gtk::ApplicationWindow::BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::ApplicationWindow(obj) {
    // FIXME try to merge init with constructor if possible

    exportDialog = nullptr;

    // setup timer label
    clock = nullptr;
    builder->get_widget_derived("SessionTimer", clock);

    // collect components
    builder->get_widget("SessionWord", wordLabel);
    builder->get_widget("SessionDefinition", definitionLabel);
    builder->get_widget("SessionSwitch", sessionSwitch);

    builder->get_widget("SessionNext", nextButton);
    builder->get_widget("SessionPrevious", prevButton);
    builder->get_widget("SessionProgress", sessionProgress);

    builder->get_widget("SessionGood", goodButton);
    builder->get_widget("SessionBad", badButton);

    builder->get_widget("SessionSave", exportButton);

    // link components
    sessionSwitch->property_active().signal_changed().connect(sigc::mem_fun(*this, &SessionWindow::toggleAnswer));
    nextButton->signal_clicked().connect(sigc::mem_fun(*this, &SessionWindow::nextWord));
    prevButton->signal_clicked().connect(sigc::mem_fun(*this, &SessionWindow::previousWord));

    goodButton->signal_clicked().connect(sigc::mem_fun(*this, &SessionWindow::goodWord));
    badButton->signal_clicked().connect(sigc::mem_fun(*this, &SessionWindow::badWord));

    exportButton->signal_clicked().connect(sigc::mem_fun(*this, &SessionWindow::exportHard));
}

void SessionWindow::init(structs::Session &ses) {
    session = ses;
    currentIndex = 0;
    answerVisible = false;
    hardWords.clear();
    refresh();
    clock->reset();
    logger::log("Initialized new session!");
}

void SessionWindow::nextWord() {
    if (currentIndex < session.records.size() - 1) {
        answerVisible = false;
        sessionSwitch->set_state(false);
        currentIndex++;
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
    if (session.records.size() > 1) {
        session.records.erase(session.records.begin() + currentIndex);
        logger::log("Removed word from session");
    }
    answerVisible = false;
    sessionSwitch->set_state(false);
    refresh();
}

void SessionWindow::badWord() {
    parser::ParsedCsvRecord *entry = &session.records.at(currentIndex);
    answerVisible = false;
    sessionSwitch->set_state(false);
    hardWords.push_back(*entry);

    logger::log("Logged hard word to buffer");
    goodWord(); // lmao don't question it
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

    // make next/ prev buttons (not) interactable
    prevButton->set_sensitive(currentIndex > 0);
    nextButton->set_sensitive(currentIndex < session.records.size() - 1);

    // export interactable
    exportButton->set_sensitive(!hardWords.empty());

    // progress
    const std::string progressText = std::to_string(currentIndex + 1) + " / " + std::to_string(session.records.size());
    sessionProgress->set_text(progressText);
    double frac = (currentIndex + 1) / (double) session.records.size();
    sessionProgress->set_fraction(frac);
}

void SessionWindow::exportResponded(int response) {
    if (response == GTK_RESPONSE_OK || response == GTK_RESPONSE_YES) {
        std::string filepath = exportDialog->get_filename();

        std::string result = parser::records_to_string(hardWords);
        utils::write_string_to_file(filepath, result);
        logger::log("Exported hard words to " + filepath);
    } else {
        logger::warn("Gave unexpected response " + std::to_string(response));
    }
    delete exportDialog;
    exportDialog = nullptr;
}

void SessionWindow::exportHard() {
    logger::log("Exporting hard words");
    exportDialog = picker::allocate_save_csv_dialog();
    exportDialog->signal_response().connect(sigc::mem_fun(*this, &SessionWindow::exportResponded));
    exportDialog->show();
}

