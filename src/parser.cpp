#include "parser.hpp"
#include "utils.hpp"

std::vector<parser::ParsedCsvRecord> parser::string_to_records(const std::string &content) {
    auto vec = std::vector<ParsedCsvRecord>();

    unsigned int index = 0;
    unsigned int len = content.length();
    while (index <= len) {
        unsigned int endIndex = content.find('\n', index+1);
        std::string line;
        if (endIndex < THRESHOLD) {
            line = content.substr(index, endIndex - index);
        }else{
            // reached the end
            line = content.substr(index);
        }

        // remove newline in line (if any)
        std::erase(line,'\n');
        std::erase(line,'\r');

        // parse the line comma or semicolon
        unsigned comma = line.find(';');
        if (comma > THRESHOLD) {
            comma = line.find(',');
        }

        if (comma < THRESHOLD) {
            vec.push_back(ParsedCsvRecord{
                .word = line.substr(0,comma),
                .definition = line.substr(comma+1),
            });
        }else{
            utils::error("Failed to parse line " + line);
        }

        index = endIndex;
    }

    return vec;
}

void parser::test_string_to_records(){
    auto result = string_to_records("hello,world\nfoo,bar\nbuzz,bazz");
    if (!result.empty()){
        for (const auto& record : result){
            std::cout << record.word << " : " << record.definition << std::endl;
        }
    }else{
        utils::error("test_string_to_records returned empty");
    }

    result = string_to_records("hello,world");
    if (!result.empty()){
        for (const auto& record : result){
            std::cout << record.word << " : " << record.definition << std::endl;
        }
    }else{
        utils::error("test_string_to_records returned empty");
    }
}

std::string parser::records_to_string(std::vector<ParsedCsvRecord> &records) {
    std::string result;
    for (const auto& record: records){
        result += record.definition;
        result += ';';
        result += record.word;
        result += '\n';
    }
    return result;
}

