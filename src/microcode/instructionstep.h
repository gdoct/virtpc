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
        static std::unique_ptr<StepExpression> compile(std::string &expression, Cpu *cpu);

    private:
        OperatorType operandType;
        GenericInt *source;
        GenericInt *target;
        GenericInt operandResult; // for logical operations
};

class InstructionStep {
    public:
        InstructionStep(int stepid) : stepid(stepid), expressions(std::vector<StepExpression>()) {}
        InstructionStep(int stepid, std::vector<StepExpression> expressions) : stepid(stepid), expressions(expressions) {}
        //InstructionStep(std::vector<StepExpression> expressions) : stepid(0), expressions(expressions) {}

        //// Delete the copy constructor and the copy assignment operator
        ////InstructionStep(const InstructionStep&) = delete;
        ////InstructionStep& operator=(const InstructionStep&) = delete;

        void execute();

        const uint8_t stepid;
        std::vector<StepExpression> expressions;
};

#endif