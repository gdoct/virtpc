#ifndef MACHINE_H
#define MACHINE_H
#include "bus.h"
#include "cpu.h"
#include "clock.h"
#include "mem.h"
#include <iostream>

class Machine {
public:
    Bus *GetBus() const;
    Cpu *GetCpu() const;
    Clock *GetClock() const;

    void Step() const;

private:
    std::unique_ptr<Bus> bus = std::make_unique<Bus>();
    std::unique_ptr<Clock> clock = std::make_unique<Clock>();
    std::unique_ptr<Cpu> cpu = std::make_unique<Cpu>(new Cpu(bus.get(), clock.get()));
};

#endif