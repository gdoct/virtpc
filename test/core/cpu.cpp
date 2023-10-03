#include "cpu.h"
#include "../tests.h"
#include "../../src/core/cpu.h"

bool cpu_shouldcreate() {

    ASSERT(true, "fail");
    return true;
}

void CpuTests::register_tests() {
    UNIT_TEST(cpu_shouldcreate);
}