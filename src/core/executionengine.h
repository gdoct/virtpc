#include <string>
#include <unordered_map>
#include "cpu.h"
#include "opcodes.h"
#include "../microcode/parser.h"

// the execution engine breaks down instructions to cpu micro steps that can be executed in order uninterrupted
class ExecutionEngine {
    public:
        void step(Cpu* cpu);
        ExecutionEngine(std::unordered_map<Opcodes, std::unordered_map<int, std::string>> microcode) : microcode(microcode) {}
        static ExecutionEngine* create_execution_engine(const std::string& filename);
        static std::unique_ptr<ExecutionEngine> create_execution_engine_ptr(const std::string& filename);
    private:
        int currentstep;
        Opcodes currentopcode;
        std::unordered_map<Opcodes, std::unordered_map<int, std::string>> microcode;
};

