#include "machine.h"
Machine::Machine() {
}

Cpu* Machine::get_cpu() const {
    return cpu.get();
}

void Machine::step() const {
    cpu->step();
}

