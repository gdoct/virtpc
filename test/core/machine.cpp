#include "../tests.h"
#include "machine.h"
#include "../../src/core/machine.h"

bool machine_shouldhavecpu() {
    auto m = new Machine();
    ASSERT_NOTNULL(m->get_cpu(), "cpu is null");
    return true;
}

bool machine_stepmultipletimes_shouldincreasepc() {
    auto m = new Machine();
    ASSERT_NOTNULL(m->get_cpu(), "cpu is null");
    ASSERT(m->get_cpu()->get_register_word("pc") == 0, "pc should be 0");
    for(auto i = 0; i < 20;i++)
        m->step();
    ASSERT(m->get_cpu()->get_register_word("pc") > 0, "pc should have increased")
    return true;
}

void MachineTests::register_tests(void) {
    UNIT_TEST(machine_shouldhavecpu);
    UNIT_TEST(machine_stepmultipletimes_shouldincreasepc);
}
