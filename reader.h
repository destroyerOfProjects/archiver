#ifndef CPP_PILOT_HSE_READER_H
#define CPP_PILOT_HSE_READER_H

#include <sstream>
#include <string>

#include "my_char.h"

class Reader {
public:
    void Flush();

    bool ReadBit();

    MyChar ReadKbit(uint8_t k);

    Reader(std::istream& str);

private:
    std::istream& str_;
    uint8_t buf_ = 0;
    uint8_t bit_number_ = 8;
};

#endif  // CPP_PILOT_HSE_READER_H
