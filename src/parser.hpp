#pragma once

#include <iostream>
#include <vector>

namespace parser {

    struct ParsedCsvRecord {
        std::string word;
        std::string definition;
    };

    constexpr int THRESHOLD = 1000000;

    std::vector<ParsedCsvRecord> string_to_records(const std::string &content);

    void test_string_to_records();

}