#ifndef CPU_H
#define CPU_H

#include <memory>

#include "bus.h"
#include "clock.h"
#include "cpustate.h"
#include "mem.h"
#include "opcodes.h"
#include "../api/numbers.h"
#include "../util/logger.h"

class ExecutionEngine; // forward declaration

class Cpu {
    public:
        Cpu();
        Cpu(Cpu& other);
        Cpu(Bus* cpubus, Clock* clock, Memory* memory, ExecutionEngine* engine);
        ~Cpu();
        const std::shared_ptr<Memory> get_Memory() { return memory; }
        const std::shared_ptr<ExecutionEngine> get_Engine() { return engine; }

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
        const std::shared_ptr<Memory> memory;
        const std::shared_ptr<ExecutionEngine> engine;

        Byte fetch_next_byte();
        Word fetch_next_word();
        void process_instruction(Opcodes instruction) const;
};

#endif