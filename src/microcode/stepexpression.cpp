#include "sstream"
#include <list>
#include "stepexpression.h"
#include "../util/functions.h"

const std::list<std::string> registers = {
    "a",
    "x",
    "y",
    "pc",
    "mc",
    "mem_word",
    "mem"
};

bool registerExists(std::string& name) {
    return list_contains_ignorecase(registers, name);
}

std::unordered_map<std::string, OperatorType> operatorToOperatorType = {
    { "",    OperatorType::None         },
    { "==",  OperatorType::Eq           },
    { "!=",  OperatorType::Neq          },
    { "&",   OperatorType::AndEq        },
    { "|",   OperatorType::OrEq         },
    { "||",  OperatorType::XorEq        },
    { ">",   OperatorType::Gt           },
    { "<",   OperatorType::Lt           },
    { "=",   OperatorType::AssignTo     },
    { ":=",  OperatorType::AssignTo     },
    { "+=",  OperatorType::AddTo        },
    { "-=",  OperatorType::SubtractTo   },
    { "*=",  OperatorType::MultiplyTo   },
    { "/=",  OperatorType::DivideTo     },
    { "&=",  OperatorType::AndTo        },
    { "!=",  OperatorType::OrTo         },
    { "&&=", OperatorType::XorTo        }
};

bool is_conditional(OperatorType op) {
    switch (op) {
        case OperatorType::Eq:
        case OperatorType::Neq:
        case OperatorType::AndEq:
        case OperatorType::OrEq:
        case OperatorType::XorEq:
        case OperatorType::Gt:
        case OperatorType::Lt:
            return true;
        default:
            return false;
    }
}

bool operatorExists(const std::string& op) {
    return operatorToOperatorType.count(op) > 0;
}

struct PreOperation {
    std::string var1;
    std::string operation;
    std::string var2;
};

GenericGetter get_getter(const std::string& var) {
    if (string_compare_ignorecase("mem_word", var)) {
        return [](Cpu* cpu) {  GenericInt gi{}; gi.u16 = cpu->get_Memory()->read_word(cpu->get_mc()); return gi; };
    }
    if (string_compare_ignorecase("pc", var)) {
        return [](Cpu* cpu) {  GenericInt gi{}; gi.u16 = cpu->get_pc(); return gi; };
    }
    if (string_compare_ignorecase("mc", var)) {
        return [](Cpu* cpu) {  GenericInt gi{}; gi.u16 = cpu->get_mc(); return gi; };
    }
    if (string_compare_ignorecase("mem", var)) {
        return [](Cpu* cpu) { GenericInt gi{}; gi.u8 = cpu->get_Memory()->read_byte(cpu->get_mc()); return gi; };
    }
    if (string_compare_ignorecase("x", var)) {
        return [](Cpu* cpu) {  GenericInt gi{}; gi.u8 = cpu->get_x(); return gi; };
    }
    if (string_compare_ignorecase("y", var)) {
        return [](Cpu* cpu) {  GenericInt gi{}; gi.u8 = cpu->get_y(); return gi; };
    }
    if (string_compare_ignorecase("a", var)) {
        return [](Cpu* cpu) {  GenericInt gi{}; gi.u8 = cpu->get_acc(); return gi;  };
    }
    return [](Cpu* cpu) { GenericInt gi{}; return gi; };
}

GenericSetter get_setter(const std::string& var) {
    if (string_compare_ignorecase("mem_word", var)) {
        return [](Cpu* cpu, GenericInt value) {  cpu->get_Memory()->write(cpu->get_mc(), value.u16); };
    }
    if (string_compare_ignorecase("mem", var)) {
        return [](Cpu* cpu, GenericInt value) { cpu->get_Memory()->write(cpu->get_mc(), value.u8);};
    }
    if (string_compare_ignorecase("pc", var)) {
        return [](Cpu* cpu, GenericInt value) {  cpu->set_pc(value.u16);};
    }
    if (string_compare_ignorecase("mc", var)) {
        return [](Cpu* cpu, GenericInt value) {  cpu->set_mc(value.u16);};
    }
    if (string_compare_ignorecase("x", var)) {
        return [](Cpu* cpu, GenericInt value) {  cpu->set_x(value.u8);};
    }
    if (string_compare_ignorecase("y", var)) {
        return [](Cpu* cpu, GenericInt value) {  cpu->set_y(value.u8);};
    }
    if (string_compare_ignorecase("a", var)) {
        return [](Cpu* cpu, GenericInt value) {  cpu->set_acc(value.u8); };
    }
    return [](Cpu* cpu, GenericInt gi){};
}

bool parseOperation(const std::string& str, PreOperation &op) {
    std::istringstream iss(str);
    iss >> op.var1 >> op.operation >> op.var2;
    return registerExists(op.var1) && operatorExists(op.operation) && registerExists(op.var2);
}

std::shared_ptr<StepExpression> StepExpression::compile(std::string& expression) {
    if (expression.empty()) {
        throw std::invalid_argument("empty expression in microcode: " + expression);
    }
    PreOperation po;
    auto works = parseOperation(expression, po);
    if (!works) {
        throw std::invalid_argument("invalid expression in microcode: " + expression);
    }

    OperatorType ot = operatorToOperatorType[po.operation];
    GenericGetter getter1 = get_getter(po.var1);
    GenericSetter setter1 = get_setter(po.var1);
    GenericGetter getter2 = get_getter(po.var2);
    return std::make_shared<StepExpression>(ot, getter1, setter1, getter2);
}

void StepExpression::execute(Cpu* cpu) {
    Log::info("executing microcode substep");
    switch (operandType) {
        case OperatorType::AssignTo: {
            var1set(cpu, var2get(cpu));
            break;
        }
        default: break;
    }
}

bool StepExpression::is_condition() {
    return is_conditional(this->operandType);
}

bool StepExpression::is_true() {
    return true;
}