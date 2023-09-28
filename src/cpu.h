#ifndef CPU_H
#define CPU_H
#include "bus.h"
#include "clock.h"
#include "cpustate.h"
#include "logger.h"

using word = char;

class Cpu {
    public:
        Cpu(Bus* bus, Clock* clock);

        word get_x();
        void set_x(word x);
        word get_y();
        void set_y(word y);
        word get_acc();
        void set_acc(word acc);
        word get_pc();
        void set_pc(word pc);
        word get_status();
        void set_status(word status);

        void fetch();
        void decode();
        void execute();

    private: 
        void clocktick();

        word x;
        word y;
        word acc;
        word pc;
        word status;

        Bus* bus;
        CpuState state;
        int statestep;
};

#endif