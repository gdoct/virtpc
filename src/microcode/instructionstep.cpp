#include "instructionstep.h"

void InstructionStep::execute(Cpu* cpu) {
    Log::info("executing microcode step " + std::to_string(this->stepid));
    for (auto& expression : expressions) {
        expression->execute(cpu);
    }
}

void InstructionStep::compile() {
    expressions.clear();
    for (auto& expression : expressionstrings) {
        auto compiled = StepExpression::compile(expression);
        expressions.push_back(compiled);
    }
}