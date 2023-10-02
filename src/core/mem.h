#ifndef MEM_H
#define MEM_H
#include <iostream>
#include <string>
#include <unordered_map>
#include "numbers.h"
#include "../util/logger.h"

struct MemoryOptions {
    MemoryOptions(int size);
    const int size;
    bool throwOutOfBounds;
};

class Memory {
    public: 
        Memory();
        Memory(Memory& other);
        Memory(MemoryOptions options);
        
        Byte read_byte(Word address);
        Word read_word(Word address);
        void write(Word address, Byte value);
        void write(Word address, Word value);
        void clear();

        void dump(std::string& filename);
        void load(std::string& filename);
        
        int get_size();

    private:
        const int size;
        std::unordered_map<Word, Byte> memory;
};
#endif