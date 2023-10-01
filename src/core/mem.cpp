#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdint>
#include "mem.h"
#include "numbers.h"
#include "../util/exception.h"

using namespace std;

string convertToString(uint8_t value) {
    char result[2];
    result[0] = static_cast<char>((value >> 8) & 0xFF);
    result[1] = static_cast<char>(value & 0xFF);
    return (string) result;
}

Memory::Memory(int size) : size(size) {
}

Byte Memory::read_byte(Word address) {
    if (address >= size) {
        return 0;
    }
    if (memory.count(address) == 0) {
        return 0;
    }
    return memory[address];
}

Word Memory::read_word(Word address) {
    if (address >= size) {
        return 0;
    }
    auto high = memory[address];
    auto low = memory[address + 1];
    return ((Word)high << 8) | low;
}

void Memory::write(Word address, Byte value) {
    if (address >= size) {
        return;
    }
    memory[address] = value;
}

void Memory::write(Word address, Word value) {
    if (address >= size) {
        return;
    }
    auto high = (Byte)((value & 0xFF00) >> 8);
    auto low = (Byte)(value & 0x00FF);
    memory[address] = high;
    memory[address + 1] = low;
}

void Memory::clear() {
    memory.clear();
}

void Memory::dump(string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (file) {
        for (auto i = 0; i < size; i++) {
            // sonarqube insists that a char* is not done nowadays
            auto result = convertToString(memory[i]).c_str();
            file.write(result, 2);
        }
        file.close();
        Log::info("Data dumped to file: " + filename);
    } else {
        Log::error("Failed to open file: " + filename);
    }
}

void Memory::load(string& filename) {
    clear();
    std::ifstream file(filename, std::ios::binary);
    if (file) {
        for (auto i = 0; i < size; i++) {
            char numAsChar[1];
            file.read(numAsChar, sizeof(numAsChar));
            memory[i] = 0; 
        }
        file.close();
        Log::info("Data loaded from file: " + filename);
    } else {
        Log::error("Failed to open file: " + filename);
    }
}