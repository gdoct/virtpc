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
        Cpu();
        Cpu(Cpu& other);
        Cpu(Bus* cpubus, Clock* clock, Memory* memory);

        Memory* get_Memory() const { return memory.get(); }

        Byte get_x() const;
        void set_x(Byte x);

        Byte get_y() const;
        void set_y(Byte y);

        Byte get_acc() const;
        void set_acc(Byte acc);

        Word get_pc() const;
        void set_pc(Word pc);

        Word get_mc() const;
        void set_mc(Word mc);

        Byte get_status() const;
        void set_status(Byte status);

        void step();

    private: 
        void clocktick();

        Byte x;
        Byte y;
        Byte acc;
        Word pc;
        Word mc;
        Byte status;

        const std::unique_ptr<Bus> bus;
        const std::unique_ptr<Clock> clock;
        const std::unique_ptr<Memory> memory;
        Byte fetch_next_byte();
        Word fetch_next_word();
        void process_instruction(Opcodes instruction) const;
};

#endif