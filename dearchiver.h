#ifndef CPP_PILOT_HSE_DEARCHIVER_H
#define CPP_PILOT_HSE_DEARCHIVER_H

#include <fstream>
#include <string>

#include "my_char.h"
#include "trie.h"
#include "reader.h"


class Dearchiver {
public:
    Dearchiver(const std::string& arhive_name);

    std::map<MyChar, Trie::Code> GetCodes(Reader& reader) const;

    MyChar ReadSymbol(Reader& reader, const Trie& trie) const;

    std::string ReadFilename(const Trie& trie, Reader& reader);

    void Build();

private:
    std::ifstream input_;
};

#endif  // CPP_PILOT_HSE_DEARCHIVER_H
