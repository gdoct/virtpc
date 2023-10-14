#ifndef CORE_CPU_H
#define CORE_CPU_H

#include <memory>
#include <map>
#include <list>
#include "clock.h"
#include "mem.h"
#include "../api/numbers.h"
#include "../util/logger.h"
#include "../util/functions.h"

class ExecutionEngine; // forward declaration

const Byte STATUS_CARRY       = 0x01; 
const Byte STATUS_ZERO        = 0x02; 
const Byte STATUS_IRQ_DISABLE = 0x04; 
const Byte STATUS_DECIMAL     = 0x08; 
const Byte STATUS_BREAK       = 0x10; 
const Byte STATUS_UNUSED      = 0x20; 
const Byte STATUS_OVERFLOW    = 0x40; 
const Byte STATUS_NEGATIVE    = 0x80; 

class Cpu {
    public:
        // constructors
        Cpu();
        Cpu(Cpu& other);
        Cpu(Clock* clock, Memory* memory, ExecutionEngine* engine);
        ~Cpu();

        // basic operations
        void step();

        // public access to memory and execution engine
        const std::shared_ptr<Memory> get_memory() { return memory; }
        const std::shared_ptr<ExecutionEngine> get_engine() { return engine; }

        // register operations
        Byte get_register(const std::string& name);
        Word get_register_word(const std::string& name);
        void set_register(const std::string& name, Byte value);
        void set_register_word(const std::string& name, Word value);

        // stack operations
        void push_stack(Byte value);
        void push_stack(Word value);
        Byte pop_stack_byte();
        Word pop_stack_word();

        // status register operations
        void set_status(Byte state_to_add);
        bool has_status(Byte state);
        void clear_status(Byte state_to_remove);

    private: 
        void clocktick();
        const std::unique_ptr<Clock> clock;
        const std::shared_ptr<Memory> memory;
        const std::shared_ptr<ExecutionEngine> engine;

        // todo initialize from configuration
        std::map<std::string, Byte> registers = { 
            {"acc", 0 },
            {"x", 0},
            {"y", 0},
            {"status", 0},
            {"sp", 0xff},
            {"pc_low", 0}, 
            {"pc_high", 0},
            {"mc_low", 0},
            {"mc_high", 0}
        };

        std::list<std::string> wideregisters = { 
            {"pc"},
            {"mc"}
        };
};

#endif