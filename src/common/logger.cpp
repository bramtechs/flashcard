#include "logger.hpp"
#include <cassert>

void logger::log(const std::string &text) {
    std::cout << "[INFO]: " << text << std::endl;
}

void logger::warn(const std::string &text) {
    std::cout << "[WARN]: " << text << std::endl;
}

void logger::error(const std::string &text) {
    std::cout << "[ERROR]: " << text << std::endl;
}

void logger::logAssert(const std::string &text, bool condition) {
    if (!condition) {
        error(text);
    }
    assert(condition);
}
