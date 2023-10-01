#include "microinstruction.h"

MicroInstruction MicroInstruction::parse(string* data) {
    auto i = MicroInstruction();
    Log::warn(data);
    return i;
}

void MicroInstruction::execute(Cpu* cpu) {
    Log::warn("not implemented: execute microcode");
    auto acc = cpu->get_acc();
    printf("%d", acc);
}