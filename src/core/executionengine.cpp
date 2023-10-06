#include "executionengine.h"

using namespace std;

void ExecutionEngine::step(Cpu* cpu) {
    if (cpu == nullptr) {

    }
}

ExecutionEngine* ExecutionEngine::create_execution_engine(const std::string& filename) {
    Parser p;
    auto mc = p.read_microcode_table(filename);
    return new ExecutionEngine(mc);
}

std::unique_ptr<ExecutionEngine> ExecutionEngine::create_execution_engine_ptr(const std::string& filename) {
    Parser p;
    auto mc = p.read_microcode_table(filename);
    return make_unique<ExecutionEngine>(mc);
}