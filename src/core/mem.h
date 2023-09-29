#ifndef MEM_H
#define MEM_H
#include <iostream>
#include <unordered_map>
#include "numbers.h"

class Memory {
    public:
        Byte read_memory(Word address);
        void write_memory(Word address, Byte value);
        void clear();
    private:
        std::unordered_map<Word, Byte> memory;
};
#endif