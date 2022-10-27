#pragma once

#include <iostream>

namespace logger {
    void log(const std::string &text);

    void warn(const std::string &text);

    void error(const std::string &text);

    void logAssert(const std::string &text, bool condition);
}