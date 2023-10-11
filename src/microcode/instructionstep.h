#ifndef INSTRUCTIONSTEP_H
#define INSTRUCTIONSTEP_H

#include <string>
#include <unordered_map>
#include <vector>
#include <string>
#include "../core/opcodes.h"
#include "../core/cpu.h"
#include "../util/logger.h"

/*
"InstructionStep" : {
    "stepid" : 1,
    "assignments" : [
        "StepExpression" {
            "operandType" : "&=",
            "source" : "[] cpu->get_a()",
            "target" : "[] cpu->get_x()",
            "operandResult" : "[r] cpu->set_a(r)",
        }, ...
    ]
}

*/


typedef union {
    Byte u8;
    Word u16;
} GenericInt;

enum class OperatorType {
    None,
    Eq,
    Neq,
    AndEq,
    OrEq,
    XorEq,
    Gt,
    Lt,

    AssignTo,
    AddTo,
    SubtractTo,
    MultiplyTo,
    DivideTo,
    AndTo,
    OrTo,
    XorTo
};

class StepExpression {
    public:
        StepExpression() = default;
        void execute();
        static std::shared_ptr<StepExpression> compile(std::string &expression, Cpu *cpu);

    private:
        OperatorType operandType;
        GenericInt *source;
        GenericInt *target;
        GenericInt operandResult; // for logical operations
};

class InstructionStep {
    public:
        InstructionStep() : expressions(std::vector<std::shared_ptr<StepExpression>>()), expressionstrings(std::vector<std::string>()) {}
        InstructionStep(int stepid, std::vector<std::shared_ptr<StepExpression>> expressions, std::vector<std::string> expressionstrings) : stepid(stepid), expressions(expressions), expressionstrings(expressionstrings) {}

        void execute();
        void compile(Cpu* cpu);
        Byte stepid = 1;
        Word instruction = 0;
        std::vector<std::shared_ptr<StepExpression>> expressions;
        std::vector<std::string> expressionstrings;
};

#endif