#include "../tests.h"
#include "../../src/api/constants.h"
#include "../../src/core/mem.h"

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
    ASSERT(val == 0, "value shouod be zero");
    return true;
}

 static bool memory_loadshouldload() {
     auto mem = new Memory(65536);
     auto fname = Paths::get_path(C64_BASIC_KERNAL_FILENAME);
     mem->load(fname, 0xc000);
     auto val = mem->read_word(0xfffc);
     ASSERT(val == 64738, "rom was not loaded");
     return true;
 }
  
void MemoryTests::register_tests() {
    UNIT_TEST(memory_loadshouldload);
    UNIT_TEST(memory_shouldstore);
    UNIT_TEST(memory_shouldreturnzero);
    UNIT_TEST(memory_beyondbounds_shouldnotcrash);
}

