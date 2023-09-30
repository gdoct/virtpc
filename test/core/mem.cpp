#include "mem.h"
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
    return false;
}

static bool memory_shouldcrash() {
    throw 42;
}

TestRunResult MemoryTests::RunAll() {
    TestRunResult result;
    int passed = 0;
    int testcount = 15;
    passed += run_test("memory_shouldstore", &memory_shouldstore);
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