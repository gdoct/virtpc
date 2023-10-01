#include "machine.h"

Cpu* Machine::GetCpu() const {
    return cpu.get();
}

Bus* Machine::GetBus() const {
    return bus.get();
}

Clock* Machine::GetClock() const {
    return clock.get();
}

void Machine::Step() const {
    clock->step();
}

