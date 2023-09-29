#ifndef CPU_H
#define CPU_H

#include "bus.h"
#include "clock.h"
#include "cpustate.h"
#include "mem.h"
#include "numbers.h"
#include "opcodes.h"

#include "../util/logger.h"

class Cpu {
    public:
        Cpu(Bus* bus, Clock* clock);

        Byte get_x();
        void set_x(Byte x);
        Byte get_y();
        void set_y(Byte y);
        Byte get_acc();
        void set_acc(Byte acc);
        Byte get_pc();
        void set_pc(Byte pc);
        Byte get_status();
        void set_status(Byte status);

        void step();

    private: 
        void clocktick();
        Memory memory;

        Byte x;
        Byte y;
        Byte acc;
        Word pc;
        Byte status;

        Bus* bus;
        Byte fetch_next_byte();
        void process_instruction(Opcodes instruction);
};

#endif