#include "mem.h"
#include "numbers.h"

Byte Memory::read_memory(Word address) {
    if (memory.count(address) == 0) {
        return 0;
    }
    return memory[address];
}

void Memory::write_memory(Word address, Byte value) {
    memory[address] = value;
}

void Memory::clear() {
    memory.clear();
}