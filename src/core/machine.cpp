#include "machine.h"
Machine::Machine() : cpu(new Cpu()) {
}

Cpu* Machine::get_cpu() const {
    return cpu.get();
}

void Machine::step() const {
    cpu->step();
}

