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
    return false;
}

static bool memory_shouldcrash() {
    throw 42;
}

void MemoryTests::RunAll(TestRunResult& result) {
    result.add_result(run_test("memory_shouldstore", &memory_shouldstore));
    result.add_result(run_test("memory_shouldreturnzero", memory_shouldreturnzero));
    result.add_result(run_test("memory_shouldcrash", memory_shouldcrash));
    result.add_result(run_test("memory_shouldstore", memory_shouldstore));
    result.add_result(run_test("memory_shouldreturnzero", memory_shouldreturnzero));
    result.add_result(run_test("memory_shouldcrash", memory_shouldcrash));
    result.add_result(run_test("memory_shouldstore", memory_shouldstore));
    result.add_result(run_test("memory_shouldreturnzero", memory_shouldreturnzero));
    result.add_result(run_test("memory_shouldcrash", memory_shouldcrash));
    result.add_result(run_test("memory_shouldstore", memory_shouldstore));
    result.add_result(run_test("memory_shouldreturnzero", memory_shouldreturnzero));
    result.add_result(run_test("memory_shouldcrash", memory_shouldcrash));
    result.add_result(run_test("memory_shouldstore", memory_shouldstore));
    result.add_result(run_test("memory_shouldreturnzero", memory_shouldreturnzero));
    result.add_result(run_test("memory_shouldcrash", memory_shouldcrash));
}