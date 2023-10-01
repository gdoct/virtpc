#include "machine.h"

Machine::~Machine() {
    delete cpu;
    delete clock;
    delete bus;
}

Machine::Machine() : bus(new Bus()), clock(new Clock()) {
    cpu = new Cpu(bus, clock);
}

Cpu* Machine::GetCpu() const {
    return cpu;
}

Bus* Machine::GetBus() const {
    return bus;
}

Clock* Machine::GetClock() const {
    return clock;
}

void Machine::Step() const {
    clock->step();
}

