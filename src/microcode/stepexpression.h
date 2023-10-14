#ifndef MICROCODE_STEPEXPRESSION_H
#define MICROCODE_STEPEXPRESSION_H

#include <string>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include "../api/numbers.h"
#include "../core/cpu.h"
#include "../util/logger.h"

using GenericGetter = std::function<GenericInt(Cpu*)>;
using GenericSetter = std::function<void(Cpu*, GenericInt&)>;

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
    // create a step from a string
    static std::shared_ptr<StepExpression> compile(std::string& expression);

    // copy constructor
    StepExpression(OperatorType operatorType, GenericGetter &lhs_get, GenericSetter &lhs_set, GenericGetter &rhs_get) :
        operatorType(operatorType), lhs_getter(lhs_get), lhs_setter(lhs_set), rhs_getter(rhs_get) {}

    // execute the step on the cpu
    void execute(Cpu* cpu);
    bool evaluate(Cpu* cpu);
    bool is_condition();
private:
    OperatorType operatorType;
    GenericGetter lhs_getter;
    GenericSetter lhs_setter;
    GenericGetter rhs_getter;
};

#endif