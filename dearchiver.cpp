#include <fstream>
#include <iostream>
#include <string>

#include "dearchiver.h"

Dearchiver::Dearchiver(const std::string& arhive_name) {
    input_ = std::ifstream(arhive_name, std::ios::binary);
    if (!input_.is_open()) {
        throw std::ios::failure("Error! File can not be open!");
    }
    Build();
}


MyChar Dearchiver::ReadSymbol(Reader& reader, const Trie& trie) const {
    Trie::Node* v = trie.root_;
    while (!v->IsLeaf()) {
        if (reader.ReadBit()) {
            v = v->GetRightChild();
        } else {
            v = v->GetLeftChild();
        }
    }
    return v->GetDataInLeaf();
}


std::map<MyChar, Trie::Code> Dearchiver::GetCodes(Reader& reader) const {
    MyChar symbols_count = reader.ReadKbit(BITS_IN_ALPHA);
    std::map<MyChar, Trie::Code> codes;

    std::vector<MyChar> alpha(symbols_count);
    for (MyChar i = 0; i < symbols_count; ++i) {
        MyChar ch = reader.ReadKbit(BITS_IN_ALPHA);
        alpha[i] = ch;
    }
    MyChar symbols_checked = 0;
    Trie::Code current_code;
    while (symbols_checked < symbols_count) {
        MyChar count = reader.ReadKbit(BITS_IN_ALPHA);
        Trie::MultTwo(current_code);
        for (int i = 0; i < count; ++i) {
            codes[alpha[symbols_checked + i]] = current_code;
            Trie::AddOne(current_code);
        }
        symbols_checked += count;
    }
    return codes;
}

std::string Dearchiver::ReadFilename(const Trie& trie, Reader& reader) {
    std::string output_name = "";
    while (true) {
        MyChar ch = ReadSymbol(reader, trie);
        if (ch == FILENAME_END) {
            break;
        }
        output_name += ch;
    }
    return output_name;
}

void Dearchiver::Build() {
    Reader reader(input_);

    while (true) {
        Trie trie;
        trie.BuildFromCodes(GetCodes(reader));

        std::ofstream output(ReadFilename(trie, reader), std::ios::binary);
        if (!output.is_open()) {
            throw std::ios::failure("Error! File can not be open!");
        }

        while (true) {
            MyChar ch = ReadSymbol(reader, trie);
            if (ch == ARCHIVE_END) {
                output.close();
                input_.close();
                return;
            }
            if (ch == ONE_MORE_FILE) {
                break;
            }
            output.put(char(ch));
        }
        output.close();
        reader.Flush();
    }
}
