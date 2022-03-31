#ifndef CPP_PILOT_HSE_ARGUMENT_PARSER_H
#define CPP_PILOT_HSE_ARGUMENT_PARSER_H

#include <vector>
#include <string>

class ArgumentParser {
public:
    ArgumentParser(int argc, char** argv);

    bool IsArchive();

    bool IsDearchive();

    bool IsHelp() const;

    std::string GetKey(size_t pos) const;

    size_t GetSize() const;

    std::string archive_name_;
    std::vector<std::string> files_;
private:
    std::vector<std::string> keys_;
};

#endif  // CPP_PILOT_HSE_ARGUMENT_PARSER_H
