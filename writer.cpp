#include "writer.h"

Writer::Writer(std::ostream& str) : str_(str), buf_(0), bit_number_(0) {
}

void Writer::Push() {
    str_.put(buf_);
    buf_ = 0;
    bit_number_ = 0;
}

void Writer::SetBit(uint8_t& mask, uint8_t bit) {
    mask |= 1 << bit;
}

void Writer::ResetBit(uint8_t& mask, uint8_t bit) {
    mask &= ~(1 << bit);
}

std::ostream& Writer::PutKbits(MyChar c, uint8_t k) {
    for (int i = 0; i < k; i++) {
        Put1bit((c >> i) & 1);
    }
    return str_;
}

void Writer::Flush() {
    if (bit_number_ != 0) {
        Push();
    }
}

std::ostream& Writer::PutKbits(std::string& code) {
    for (auto c: code) {
        Put1bit(c - '0');
    }
    return str_;
}

void Writer::Put1bit(bool b) {
    if (b) {
        SetBit(buf_, 7 - bit_number_);
    } else {
        ResetBit(buf_, 7 - bit_number_);
    }
    bit_number_ += 1;
    if (bit_number_ == COUNT_BITS_IN_BYTE) {
        Push();
    }
}
