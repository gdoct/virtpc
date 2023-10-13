#ifndef NUMBERS_H
#define NUMBERS_H

#include <cstdint>

using Byte = uint8_t;
using Word = uint16_t;

typedef union {
    Byte u8;
    Word u16;
} GenericIntUnion;

struct GenericInt {
    GenericInt() : is_word(false) {}
    GenericInt(bool word) : is_word(word) {}
    GenericInt(GenericInt& other) : value(other.value), is_word(other.is_word) {}
    GenericInt& operator=(const GenericInt& other) {
        if (this != &other) {
            // This is necessary because we can't assign to 'value' directly
            this->value.u8 = other.value.u8;
            this->value.u16 = other.value.u16;
            // No need to copy 'is_word' because it's const
        }
        return *this;
    }

    GenericInt operator+(const GenericInt& other) const {
        if (this->is_word && other.is_word) {
            Word sum = static_cast<Word>((this->value.u16 + other.value.u16) & 0xFFFF);
            auto i = GenericInt( true);
            i.value.u16 = sum;
            return i;
        } else {
            Byte sum = static_cast<Byte>((this->value.u8 + other.value.u8) & 0xFF);
            auto i = GenericInt(false);
            i.value.u8 = sum;
            return i;
        }
    }

    GenericInt operator-(const GenericInt& other) const {
        if (this->is_word && other.is_word) {
            Word diff = static_cast<Word>((this->value.u16 - other.value.u16) & 0xFFFF);
            auto i = GenericInt(true);
            i.value.u16 = diff;
            return i;
        } else {
            Byte diff = static_cast<Byte>((this->value.u8 - other.value.u8) & 0xFF);
            auto i = GenericInt(false);
            i.value.u8 = diff;
            return i;
        }
    }

    GenericInt operator*(const GenericInt& other) const {
        GenericInt result;
        if (this->is_word && other.is_word) {
            if (other.value.u16 > 0 && this->value.u16 > std::numeric_limits<Word>::max() / other.value.u16) {
                // Handle overflow...
            }
            result = GenericInt(true);
            result.value.u16 = this->value.u16 * other.value.u16;
        } else {
            if (other.value.u8 > 0 && this->value.u8 > std::numeric_limits<Byte>::max() / other.value.u8) {
                // Handle overflow...
            }
            result = GenericInt(false);
            result.value.u8 = this->value.u8 * other.value.u8;
        }
        return result;
    }

    GenericInt operator/(const GenericInt& other) const {
        GenericInt result;
        if (this->is_word && other.is_word) {
            if (other.value.u16 == 0) {
                // Handle divide by zero...
            }
            result = GenericInt(true);
            result.value.u16 = this->value.u16 / other.value.u16;
        } else {
            if (other.value.u8 == 0) {
                // Handle divide by zero...
            }
            result = GenericInt(false);
            result.value.u8 = this->value.u8 / other.value.u8;
        }
        return result;
    }


    GenericIntUnion value;
    const bool is_word;
};

#endif
