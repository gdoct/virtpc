#include "memorytests.h"
// class Memory {
//     public: 
//         Memory(int size);

//         Byte read_byte(Word address);
//         Word read_word(Word address);
//         void write(Word address, Byte value);
//         void write(Word address, Word value);
//         void clear();

//         void dump(string& filename);
//         void load(string& filename);
//     private:
//         std::unordered_map<Word, Byte> memory;
// };

static bool memory_shouldstore() {
    auto mem = Memory(16384);
    Word address = 0;
    Byte value = 42;
    mem.write(address, value);
    auto result = mem.read_byte(address);
    assert(value == result);
}

static bool memory_shouldreturnzero() {
    return false;
}

static bool memory_shouldcrash() {
    throw 42;
}

TestRunResult MemoryTests::RunAll() {
    TestRunResult result;
    int passed = 0;
    int testcount = 15;
    passed += run_test("memory_shouldstore", memory_shouldstore);
    passed += run_test("memory_shouldreturnzero", memory_shouldreturnzero);
    passed += run_test("memory_shouldcrash", memory_shouldcrash);
    passed += run_test("memory_shouldstore", memory_shouldstore);
    passed += run_test("memory_shouldreturnzero", memory_shouldreturnzero);
    passed += run_test("memory_shouldcrash", memory_shouldcrash);
    passed += run_test("memory_shouldstore", memory_shouldstore);
    passed += run_test("memory_shouldreturnzero", memory_shouldreturnzero);
    passed += run_test("memory_shouldcrash", memory_shouldcrash);
    passed += run_test("memory_shouldstore", memory_shouldstore);
    passed += run_test("memory_shouldreturnzero", memory_shouldreturnzero);
    passed += run_test("memory_shouldcrash", memory_shouldcrash);
    passed += run_test("memory_shouldstore", memory_shouldstore);
    passed += run_test("memory_shouldreturnzero", memory_shouldreturnzero);
    passed += run_test("memory_shouldcrash", memory_shouldcrash);

    result.passed = passed;
    result.failed = testcount - passed;

    return result;
}