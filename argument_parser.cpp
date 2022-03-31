#include <algorithm>
#include <string>

#include "argument_parser.h"

ArgumentParser::ArgumentParser(int argc, char** argv) {
    for (int i = 0; i < argc; ++i) {
        keys_.emplace_back(argv[i]);
    }
}

bool ArgumentParser::IsHelp() const {
    return keys_.size() == 2 && keys_[1] == "-h";
}

bool ArgumentParser::IsArchive() {
    if (keys_.size() < 4 || keys_[1] != "-c") {
        return false;
    }
    archive_name_ = keys_[2];
    for (size_t i = 3; i < keys_.size(); ++i) {
        std::string str = keys_[i];
        if (i == 4) {
            if (str[0] != '[') {
                throw std::invalid_argument("Missing [");
            }
            str.erase(str.begin());
        }
        if (str.empty()) {
            throw std::invalid_argument("Empty file");
        }
        if (i >= 4 && i + 1 == keys_.size()) {
            if (str.back() != ']') {
                throw std::invalid_argument("Missing ]");
            }
            str.pop_back();
        }
        if (str.empty()) {
            throw std::invalid_argument("Empty file");
        }
        files_.push_back(str);
    }
    return true;
}

bool ArgumentParser::IsDearchive() {
    if (keys_.size() != 3 || keys_[1] != "-d") {
        return false;
    }
    archive_name_ = keys_[2];
    return true;
}

std::string ArgumentParser::GetKey(size_t pos) const {
    if (pos < 0 || pos >= keys_.size()) {
        throw std::bad_alloc();
    }
    return keys_[pos];
}

size_t ArgumentParser::GetSize() const {
    return keys_.size();
}
