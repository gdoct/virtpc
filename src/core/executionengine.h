#ifndef CORE_EXECUTIONENGINE_H
#define CORE_EXECUTIONENGINE_H
#include <string>
#include <unordered_map>
#include "cpu.h"
#include "opcodes.h"
#include "../microcode/parser.h"

/* 

the execution engine breaks down instructions to cpu micro steps that can be executed in order uninterrupted

STEPS NEEDED FOR EXECUTING MACHINE CODE

while (true)
    step [1]   store pc in mc and increase pc
    step [2]   store mem in local "currentopcode" and set step to 0
    step [3..] execute available steps for this instruction


*/


class ExecutionEngine {
    public:
        ExecutionEngine() = default;
        ExecutionEngine(MicrocodeMap microcode) : currentstep(0), is_executing_instuction(false), currentinstruction(0), microcode(microcode) {}

        void step(Cpu* cpu);
        void raise_interrupt(Word isr_address);

        size_t currentstep = 0;
        bool is_executing_instuction = false;
        Byte currentinstruction = 0;

        static ExecutionEngine* create_execution_engine(const std::string& filename);
        static std::unique_ptr<ExecutionEngine> create_execution_engine_ptr(const std::string& filename);
    private:
        MicrocodeMap microcode;
        bool is_interrupt_raised = false;
        bool is_servicing_interrupt = false;
        Word interrupt_address = 0;
};

#endif
