#ifndef EXECUTIONEGINE_H
#define EXECUTIONEGINE_H
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
        ExecutionEngine(std::unordered_map<Byte, std::unordered_map<int, InstructionStep>> microcode) : currentstep(0), stepcount(2), currentinstruction(0), microcode(microcode) {}

        void step(Cpu* cpu);
        void compile_microcode();

        size_t currentstep = 0;
        size_t stepcount = 2;
        Byte currentinstruction = 0;

        static ExecutionEngine* create_execution_engine(const std::string& filename);
        static std::unique_ptr<ExecutionEngine> create_execution_engine_ptr(const std::string& filename);
    private:
        std::unordered_map<Byte, std::unordered_map<int, InstructionStep>> microcode;
};

#endif
