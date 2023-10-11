#include "instructionstep.h"

std::shared_ptr<StepExpression> StepExpression::compile(std::string &expression, Cpu *cpu) {
    if (expression == "" || cpu == nullptr) {

    }
    return std::make_shared<StepExpression>();
}

void StepExpression::execute() {
    Log::info("executing microcode substep");
}

void InstructionStep::execute() {
    Log::info("executing microcode step " + std::to_string(this->stepid));
    for (auto& expression : expressions) {
        expression->execute();
    }
}

void InstructionStep::compile(Cpu* cpu) {
    for (auto& expression : expressionstrings) {
        auto compiled = StepExpression::compile(expression, cpu);
        expressions.push_back(compiled);
    }
}