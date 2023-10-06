#ifndef CPU_H
#define CPU_H

#include <memory>

#include "bus.h"
#include "clock.h"
#include "cpustate.h"
#include "mem.h"
#include "numbers.h"
#include "opcodes.h"
#include "../util/logger.h"

class ExecutionEngine; // forward declaration

class Cpu {
    public:
        Cpu();
        Cpu(Cpu& other);
        Cpu(Bus* cpubus, Clock* clock, Memory* memory, ExecutionEngine* engine);
        ~Cpu();
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

        Byte x      = 0;
        Byte y      = 0;
        Byte acc    = 0;
        Word pc     = 0;
        Word mc     = 0;
        Byte status = 0;

        const std::unique_ptr<Bus> bus;
        const std::unique_ptr<Clock> clock;
        const std::unique_ptr<Memory> memory;
        std::unique_ptr<ExecutionEngine> engine;

        Byte fetch_next_byte();
        Word fetch_next_word();
        void process_instruction(Opcodes instruction) const;
};

#endif