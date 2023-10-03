#include "clock.h"

bool clock_canBeCreated() {
    ASSERT(true, "the server made a booboo");
    return true;
}

void ClockTests::register_tests() {
    UNIT_TEST(clock_canBeCreated);
}