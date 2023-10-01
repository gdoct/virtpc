#include "../tests.h"
#include "../../src/core/mem.h"

static bool memory_shouldstore() {
    auto mem = Memory(16384);
    Word address = 0;
    Byte value = 42;
    mem.write(address, value);
    auto result = mem.read_byte(address);
    bool expected = value == result;
    return TestBase::assert_true(expected);
}

static bool memory_shouldreturnzero() {
    auto mem = Memory(16384);
    auto val = mem.read_byte(1234);
    const Byte expected = 0;
    return expected == val;
}

static bool memory_shouldcrash() {
    try {
    auto mem = Memory(100);
    // read beyond bounds should crash
    auto val = mem.read_byte(1234);
    } 
    catch(void *) 
    {
        return true;
    }
    return false;
}

void MemoryTests::register_tests() {
    UNIT_TEST(memory_shouldstore);
    UNIT_TEST(memory_shouldreturnzero);
    UNIT_TEST(memory_shouldcrash);
}