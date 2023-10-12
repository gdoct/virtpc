#ifndef STEPEXPRESSION_H
#define STEPEXPRESSION_H

#include <string>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <functional>

#include "../core/cpu.h"
#include "../util/logger.h"

typedef union {
    Byte u8;
    Word u16;
} GenericInt;

using GenericGetter = std::function<GenericInt(Cpu*)>;
using GenericSetter = std::function<void(Cpu*, GenericInt)>;

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
    StepExpression(OperatorType operandType, GenericGetter &var1get, GenericSetter &var1set, GenericGetter &var2get) :
        operandType(operandType), var1get(var1get), var1set(var1set), var2get(var2get) {}

    void execute(Cpu* cpu);
    static std::shared_ptr<StepExpression> compile(std::string& expression);

private:
    OperatorType operandType;
    GenericGetter var1get;
    GenericSetter var1set;
    GenericGetter var2get;
    bool is_true();
    bool is_condition();
};

#endif