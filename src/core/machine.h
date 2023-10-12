#ifndef MACHINE_H
#define MACHINE_H
#include "cpu.h"
#include "clock.h"
#include "mem.h"
#include <iostream>

class Machine {
public:
    Machine(); 
    Cpu *get_cpu() const;
    void step() const;

private:
    const std::unique_ptr<Cpu> cpu;
};

#endif