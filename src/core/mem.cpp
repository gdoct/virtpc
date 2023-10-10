#include <fstream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include "mem.h"
#include "../api/constants.h"
#include "../api/numbers.h"
#include "../util/exception.h"

MemoryOptions::MemoryOptions(int size) : size(size), throwOutOfBounds(true) {}

Memory::Memory(Memory& other) : size(other.size), memory(other.memory) { }
Memory::Memory(MemoryOptions options) : size(options.size), memory(options.size) { clear(); }
Memory::Memory() : size(4096), memory(4096) { clear(); }

Byte Memory::read_byte(Word address) {
    if (address >= size) {
        return 0;
    }
    return memory[address];
}

Word Memory::read_word(Word address) {
    int index = static_cast<int>(address);
    if ((index + 1) >= size) {
        return 0;
    }
    auto low = memory[index];
    auto high = memory[index + 1];
    return ((Word)high << 8) | low;
}

void Memory::write(Word address, Byte value) {
    int index = static_cast<int>(address);
    if (index >= size) {
        return;
    }
    memory[index] = value;
}

void Memory::write(Word address, Word value) {
    int index = static_cast<int>(address);
    if ((index + 1) >= size) {
        return;
    }
    auto high = (Byte)((value & 0xFF00) >> 8);
    auto low = (Byte)(value & 0x00FF);
    memory[index] = low;
    memory[index + 1] = high;
}

void Memory::clear() {
    for (auto addr = 0; addr < size; addr++) {
        memory[addr] = 0;
    }
}

bool writeToFile(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(data.data()), data.size());
        return true;
    }
    return false;
}

std::vector<Byte> readFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<Byte> buffer(size);
        if (file.read(reinterpret_cast<char*>(buffer.data()), size)) {
            return buffer;
        }
    }
    return {};
}


void Memory::dump(const std::string& filename) {
    auto file = writeToFile(filename, memory);
    if (file) {
        Log::info("Data dumped to file: " + filename);
    } else {
        Log::error("Failed to dump to file: " + filename);
    }
}

void Memory::load(const std::string& filename, Word address) {
    clear();
    int addr = static_cast<int>(address);
    auto data = readFromFile(filename);
    int datasize = static_cast<int>(data.size());
    if ((addr + datasize) > size) {
        throw E_OVERFLOW;
    }
    if (datasize > 0) {
        for (int i = 0; i < datasize; i++) {
            memory[addr + i] = data[i];
        }
        Log::info("Data loaded from file: " + filename);
    } else { 
        Log::error("Failed to open file: " + filename);
    }
}

int Memory::get_size() { 
    return size; 
}