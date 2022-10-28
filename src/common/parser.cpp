#include "parser.hpp"
#include "logger.hpp"

std::vector<parser::ParsedCsvRecord> parser::string_to_records(const std::string &content) {
    auto vec = std::vector<ParsedCsvRecord>();

    unsigned int index = 0;
    unsigned int len = content.length();
    while (index <= len) {
        unsigned int endIndex = content.find('\n', index + 1);
        std::string line;
        if (endIndex < THRESHOLD) {
            line = content.substr(index, endIndex - index);
        } else {
            // reached the end
            line = content.substr(index);
        }

        // remove newlines in csv line
        std::erase(line, '\n');
        std::erase(line, '\r');

        // check if not a comment
        if (line.find('#') != 0) {

            // chop the line by semicolon (or comma)
            unsigned comma = line.find(';');
            if (comma > THRESHOLD) {
                comma = line.find(',');
            }

            if (comma < THRESHOLD) {

                // if double card, add mirror
                if (line.find('$') == 0) {

                    vec.push_back(ParsedCsvRecord{
                            .word = line.substr(comma + 1),
                            .definition = line.substr(1, comma - 1),
                    });
                    vec.push_back(ParsedCsvRecord{
                            .word = line.substr(1, comma - 1),
                            .definition = line.substr(comma + 1),
                    });
                } else { // normal card
                    vec.push_back(ParsedCsvRecord{
                            .word = line.substr(0, comma),
                            .definition = line.substr(comma + 1),
                    });
                }

            } else {
                logger::error("Failed to parse line " + line);
            }

        } else {
            logger::log("Skipping comment... " + line);
        }
        index = endIndex;
    }

    return vec;
}

void parser::test_string_to_records() {
    auto result = string_to_records("hello,world\nfoo,bar\nbuzz,bazz");
    if (!result.empty()) {
        for (const auto &record: result) {
            std::cout << record.word << " : " << record.definition << std::endl;
        }
    } else {
        logger::error("test_string_to_records returned empty");
    }

    result = string_to_records("hello,world");
    if (!result.empty()) {
        for (const auto &record: result) {
            std::cout << record.word << " : " << record.definition << std::endl;
        }
    } else {
        logger::error("test_string_to_records returned empty");
    }
}

std::string parser::records_to_string(std::vector<ParsedCsvRecord> &records) {
    std::string result;
    for (const auto &record: records) {
        result += record.definition;
        result += ';';
        result += record.word;
        result += '\n';
    }
    return result;
}

