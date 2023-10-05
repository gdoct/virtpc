#include "executionengine.h"
#include "../microcode/parser.h"

using namespace std;

ExecutionEngine::ExecutionEngine(unordered_map<Opcodes, unordered_map<int, string>> microcode) : microcode(microcode) {}

unique_ptr<ExecutionEngine> ExecutionEngine::create(const string& filename) {
    Parser p;
    auto mc = p.read_microcode_table(filename);
    return make_unique<ExecutionEngine>(new ExecutionEngine(mc));
}

void ExecutionEngine::step(Cpu* cpu) {
if (cpu == nullptr) {

}
}