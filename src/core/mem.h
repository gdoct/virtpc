#ifndef MEM_H
#define MEM_H
#include <iostream>
#include <string>
#include <unordered_map>
#include "numbers.h"
#include "../util/logger.h"

class Memory {
    public: 
        explicit Memory(int size);

        Byte read_byte(Word address);
        Word read_word(Word address);
        void write(Word address, Byte value);
        void write(Word address, Word value);
        void clear();

        void dump(std::string& filename);
        void load(std::string& filename);
    private:
        std::unordered_map<Word, Byte> memory;
        const int size;
};
#endif