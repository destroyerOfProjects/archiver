#ifndef CPP_PILOT_HSE_ARCHIVER_H
#define CPP_PILOT_HSE_ARCHIVER_H

#include <string>
#include <fstream>
#include <map>

#include "my_char.h"
#include "writer.h"
#include "trie.h"

class Archiver {
public:
    Archiver(const std::string& read_path, const std::string& write_path, bool is_last_file);

    void CountOccurrences();

    void Build();

    void ResetInput();


    void CloseFiles();

    void WriteFileData(Writer& writer);

    void WriteAlpha(const std::map<int8_t, std::vector<MyChar>>& lengths, Writer& writer) const;

    void WriteLengths(const std::map<int8_t, std::vector<MyChar>>& lengths, Writer& writer) const;

    void WriteString(const std::string& str, Writer& writer);

    void FinishOutput(Writer& writer);

private:
    std::map<MyChar, size_t> count_occurrences_;
    std::ifstream input_;
    std::ofstream output_;
    std::string from_;
    std::string to_;
    bool is_last_file_;
    std::map<MyChar, Trie::Code> codes_;
};

#endif  // CPP_PILOT_HSE_ARCHIVER_H
