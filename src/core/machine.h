#ifndef MACHINE_H
#define MACHINE_H
#include "bus.h"
#include "cpu.h"
#include "clock.h"
#include "mem.h"
#include <iostream>

class Machine {
public:
    Machine();

    ~Machine();

    Bus *GetBus() const;
    Cpu *GetCpu() const;
    Clock *GetClock() const;

    void Step() const;

private:
    Cpu *cpu;
    Bus *bus;
    Clock *clock;
};

#endif