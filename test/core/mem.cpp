#include "../tests.h"
#include "../../src/core/mem.h"
#include "../../src/util/exception.h"

static bool 
memory_shouldstore(void) {
    auto mem = Memory(99);
    Word address = 69;
    Byte value = 42;
    mem.write(address, value);
    auto result = mem.read_byte(address);
    bool expected = value == result;
    return expected;
}

static bool 
memory_shouldreturnzero(void) {
    auto mem = Memory(2000);
    auto val = mem.read_byte(1234);
    const Byte expected = 0;
    return expected == val;
}

static bool 
memory_beyondbounds_shouldnotcrash(void) {
    auto mem = Memory(100);
    mem.write(1234, (Byte)42);
    auto val = mem.read_byte(1234);
    return (val == 0);
}

void MemoryTests::register_tests() {
    UNIT_TEST(memory_shouldstore);
    UNIT_TEST(memory_shouldreturnzero);
    UNIT_TEST(memory_beyondbounds_shouldnotcrash);
}