#ifndef CPP_PILOT_HSE_WRITER_H
#define CPP_PILOT_HSE_WRITER_H

#include <ostream>
#include <string>

#include "my_char.h"

class Writer {
public:
    Writer(std::ostream& str);

    void Put1bit(bool b);

    std::ostream& PutKbits(MyChar c, uint8_t k);

    std::ostream& PutKbits(std::string& code);

    void Push();

    void SetBit(uint8_t& mask, uint8_t bit);

    void ResetBit(uint8_t& mask, uint8_t bit);

    void Flush();

private:
    std::ostream& str_;
    uint8_t buf_ = 0;
    uint8_t bit_number_ = 0;
};

#endif  // CPP_PILOT_HSE_WRITER_H
