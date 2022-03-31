#include "reader.h"

void Reader::Flush() {
    bit_number_ = 8;
}

bool Reader::ReadBit() {
    if (bit_number_ == 8) {
        buf_ = str_.get();
        bit_number_ = 0;
    }
    bool result = (buf_ >> (7 - bit_number_)) & 1;
    bit_number_ += 1;
    return result;
}

Reader::Reader(std::istream& str) : str_(str), buf_(0), bit_number_(8) {
}

MyChar Reader::ReadKbit(uint8_t k) {
    MyChar result = 0;
    MyChar deg = 1;
    while (k > 0) {
        result += deg * ReadBit();
        deg *= 2;
        k -= 1;
    }
    return result;
}
