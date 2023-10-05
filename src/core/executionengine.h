#include <string>
#include <unordered_map>
#include "cpu.h"
#include "opcodes.h"
#include "../microcode/parser.h"

// the execution engine breaks down instructions to cpu micro steps that can be executed in order uninterrupted
class ExecutionEngine {
    public:
        static std::unique_ptr<ExecutionEngine> create(const std::string& filename);
        void step(Cpu* cpu);
    private:
        int currentstep;
        Opcodes currentopcode;
        std::unordered_map<Opcodes, std::unordered_map<int, std::string>> microcode;

        ExecutionEngine(std::unordered_map<Opcodes, std::unordered_map<int, std::string>> microcode) : microcode(microcode) {}
};