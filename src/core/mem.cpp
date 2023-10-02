#include <fstream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include "mem.h"
#include "numbers.h"
#include "../util/exception.h"

using namespace std;

MemoryOptions::MemoryOptions(int size) : size(size) {}

Memory::Memory(Memory& other): size(other.size), memory(other.memory) {}
Memory::Memory(MemoryOptions options) : size(options.size), memory() {}
Memory::Memory() : size(4096), memory() {}

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

std::vector<uint8_t> convertMapToVector(std::unordered_map<Word, Byte>& map, int size) {
    std::vector<uint8_t> vec;
    for (Word i=0; i < size; i++) {
        auto val = map.find(i);
        if (val == map.end()) {
            vec.push_back(0);
        }
        else {
            vec.push_back(map[i]);
        }
    }
    return vec;
}

void Memory::dump(string& filename) {
    auto data = convertMapToVector(memory, size);
    auto file = writeToFile(filename, data);
    if (file) {
        Log::info("Data dumped to file: " + filename);
    } else {
        Log::error("Failed to dump to file: " + filename);
    }
}

void Memory::load(string& filename) {
    clear();
    auto data = readFromFile(filename);
    auto datasize = data.size();
    if (datasize > 0) {
        
        for (Word i = 0; i < datasize; i++) {
            if(data[i] != 0) {
                memory[i] = data[i]; 
            }
        }
        Log::info("Data loaded from file: " + filename);
    } else {
        Log::error("Failed to open file: " + filename);
    }
}

int Memory::get_size() { 
    return size; 
}