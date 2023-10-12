#ifndef INSTRUCTIONSTEP_H
#define INSTRUCTIONSTEP_H

#include <string>
#include <unordered_map>
#include <vector>
#include <string>
#include "../core/cpu.h"
#include "../util/logger.h"
#include "stepexpression.h"

class InstructionStep {
    public:
        InstructionStep() : expressions(std::vector<std::shared_ptr<StepExpression>>()), expressionstrings(std::vector<std::string>()) {}
        InstructionStep(int stepid, std::vector<std::shared_ptr<StepExpression>> expressions, std::vector<std::string> expressionstrings) : stepid(stepid), expressions(expressions), expressionstrings(expressionstrings) {}

        void execute(Cpu* cpu);
        void compile();
        Byte stepid = 1;
        Word instruction = 0;
        std::vector<std::shared_ptr<StepExpression>> expressions;
        std::vector<std::string> expressionstrings;
};

#endif