#include "../tests.h"
#include "machine.h"
#include "../../src/core/machine.h"

bool machine_shouldhavecpu() {
    auto m = new Machine();
    ASSERT_NOTNULL(m->get_cpu(), "cpu is null");
    return true;
}

bool machine_stepshouldincreasepc() {
    auto m = new Machine();
    ASSERT_NOTNULL(m->get_cpu(), "cpu is null");
    ASSERT(m->get_cpu()->get_pc() == 0, "pc should be 0");
    m->step();
    ASSERT(m->get_cpu()->get_pc() == 1, "pc should be 1")
    return true;
}

void MachineTests::register_tests(void) {
    UNIT_TEST(machine_shouldhavecpu);
    UNIT_TEST(machine_stepshouldincreasepc);
}
