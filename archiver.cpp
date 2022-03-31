#include <algorithm>
#include <string>
#include <map>

#include "archiver.h"
#include "reader.h"
#include "trie.h"
#include "writer.h"

Archiver::Archiver(const std::string& from, const std::string& to, bool is_last_file) {
    input_ = std::ifstream(from, std::ios::binary);
    output_ = std::ofstream(to, std::ios_base::app | std::ios::binary);
    from_ = from;
    to_ = to;
    is_last_file_ = is_last_file;
    Build();
}

void Archiver::Build() {
    if (!input_.is_open() || !output_.is_open()) {
        throw std::ios::failure("Error! File can not be open!");
    }
    if (!output_.is_open()) {
        throw std::ios::failure("Error! File can not be open!");
    }
    CountOccurrences();

    Trie current_tree(count_occurrences_);
    current_tree.BuildTrie();
    auto lengths = current_tree.GetLengths();
    codes_ = current_tree.GetCodes();

    Writer writer(output_);

    ResetInput();

    writer.PutKbits(codes_.size(), BITS_IN_ALPHA);
    WriteAlpha(lengths, writer);
    WriteLengths(lengths, writer);
    WriteString(from_, writer);
    writer.PutKbits(codes_[FILENAME_END]);
    WriteFileData(writer);
    FinishOutput(writer);
    CloseFiles();
}

void Archiver::CountOccurrences() {
    for (char ch: from_) {
        count_occurrences_[ch] += 1;
    }
    char c;
    while (input_.get(c)) {
        count_occurrences_[c] += 1;
    }
    count_occurrences_[FILENAME_END] += 1;
    count_occurrences_[ONE_MORE_FILE] += 1;
    count_occurrences_[ARCHIVE_END] += 1;
}

void Archiver::ResetInput() {
    input_.clear();
    input_.seekg(0, input_.beg);
}


void Archiver::CloseFiles() {
    input_.close();
    output_.close();
}

void Archiver::WriteFileData(Writer& writer) {
    char c;
    while (input_.get(c)) {
        writer.PutKbits(codes_[c]);
    }
}

void Archiver::WriteAlpha(const std::map<int8_t, std::vector<MyChar>>& lengths, Writer& writer) const {
    for (auto&[len, vec]: lengths) {
        for (auto data: vec) {
            writer.PutKbits(data, BITS_IN_ALPHA);
        }
    }
}

void Archiver::WriteLengths(const std::map<int8_t, std::vector<MyChar>>& lengths, Writer& writer) const {
    int8_t max_code_size = 0;
    for (const auto&[len, vec]: lengths) {
        if (len > max_code_size) {
            max_code_size = len;
        }
    }
    for (int8_t len = 1; len <= max_code_size; ++len) {
        int size = 0;
        if (lengths.count(len)) {
            size = lengths.at(len).size();
        }
        writer.PutKbits(size, BITS_IN_ALPHA);
    }
}

void Archiver::WriteString(const std::string& str, Writer& writer) {
    for (auto ch: from_) {
        writer.PutKbits(codes_[ch]);
    }
}

void Archiver::FinishOutput(Writer& writer) {
    if (is_last_file_) {
        writer.PutKbits(codes_[ARCHIVE_END]);
    } else {
        writer.PutKbits(codes_[ONE_MORE_FILE]);
    }
    writer.Flush();
}

