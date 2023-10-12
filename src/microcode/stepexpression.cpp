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
        // read word from memory at given word address 
        return [var](Cpu* cpu) {  GenericInt gi{}; gi.u16 = cpu->get_memory()->read_word(cpu->get_register_word(var)); return gi; };
    } 
    else if (string_compare_ignorecase("mc", var) || string_compare_ignorecase("pc", var)) {
        // read word from register
        return [var](Cpu* cpu) {  GenericInt gi{}; gi.u16 = cpu->get_register_word(var); return gi; };
    }
    else if (string_compare_ignorecase("mem", var)) {
        // read byte from memory at location mc
        return [var](Cpu* cpu) {  GenericInt gi{}; gi.u16 = cpu->get_memory()->read_byte(cpu->get_register_word(var)); return gi; };
    } else {
        // read byte register
        return [var](Cpu* cpu) { GenericInt gi{}; gi.u8 = cpu->get_register(var); return gi; };
    }
}

GenericSetter get_setter(const std::string& var) {
    if (string_compare_ignorecase("mem_word", var)) {
        // write word to memory at given word address 
        return [var](Cpu* cpu, GenericInt value) {  cpu->get_memory()->write(cpu->get_register_word(var), value.u16); };
    } 
    else if (string_compare_ignorecase("mc", var) || string_compare_ignorecase("pc", var)) {
        // write word to register
        return [var](Cpu* cpu, GenericInt value) {  cpu->set_register_word(var, value.u16);};
    }
    else if (string_compare_ignorecase("mem", var)) {
        // write byte to memory at wide address mc
        return [var](Cpu* cpu, GenericInt value) { cpu->get_memory()->write(cpu->get_register_word(var), value.u8);};
    } else {
        // write byte register
        return [var](Cpu* cpu, GenericInt value) {  cpu->set_register(var, value.u8); };
    }
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
    switch (operatorType) {
        case OperatorType::AssignTo: {
            lhs_setter(cpu, rhs_getter(cpu));
            break;
        }
        default: break;
    }
}

bool StepExpression::is_condition() {
    return is_conditional(this->operatorType);
}

bool StepExpression::is_true() {
    return true;
}