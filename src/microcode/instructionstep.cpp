#include "instructionstep.h"

std::unique_ptr<StepExpression> StepExpression::compile(std::string &expression, Cpu *cpu) {
    if (expression == "" || cpu == nullptr) {

    }
    return std::make_unique<StepExpression>();
}

void StepExpression::execute() {
    Log::info("executing microcode substep");
}

void InstructionStep::execute() {
    Log::info("executing microcode step " + std::to_string(this->stepid));
    for (auto& expression : expressions) {
        expression.execute();
    }
}
//
//
//InstructionStep InstructionStep::create(uint8_t stepid, Byte instructionid, std::string& operation) {
//    return InstructionStep();
//}