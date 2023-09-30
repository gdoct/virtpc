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

        Word get_pc();
        void set_pc(Word pc);

        Word get_mc();
        void set_mc(Word mc);

        Byte get_status();
        void set_status(Byte status);

        void step();

        Memory* memory = new Memory(65536);

    private: 
        void clocktick();

        Byte x;
        Byte y;
        Byte acc;
        Word pc;
        Word mc;
        Byte status;

        Bus* bus;
        Byte fetch_next_byte();
        Word fetch_next_word();
        void process_instruction(Opcodes instruction);
};

#endif