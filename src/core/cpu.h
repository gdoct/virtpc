#ifndef CPU_H
#define CPU_H

#include <memory>
#include <map>
#include <list>
#include "clock.h"
#include "mem.h"
#include "../api/numbers.h"
#include "../util/logger.h"
#include "../util/functions.h"

class ExecutionEngine; // forward declaration

class Cpu {
    public:
        Cpu();
        Cpu(Cpu& other);
        Cpu(Clock* clock, Memory* memory, ExecutionEngine* engine);
        ~Cpu();

        const std::shared_ptr<Memory> get_memory() { return memory; }
        const std::shared_ptr<ExecutionEngine> get_engine() { return engine; }

        Byte get_register(const std::string& name);
        Word get_register_word(const std::string& name);

        void set_register(const std::string& name, Byte value);
        void set_register_word(const std::string& name, Word value);

        void step();
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