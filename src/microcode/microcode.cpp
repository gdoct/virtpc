#include "microcode.h"
#include <string>

/*
LDA
load word address parameter into mc
load memory into accum

STA
load word address parameter into mc
store accum into memory
*/
Microcode Microcode::load() {
    Microcode mc;
    return mc;
}

int Microcode::get_step_count(Opcodes instruction) const {
    if ((Byte)instruction >= 1)
        return 0;
    else 
        return 4;
}

MicroInstruction Microcode::get_step(Opcodes instruction, int step) const {
    if (step > 0) {
        auto p = step % (Byte) instruction;
        if (p > 0) Log::error("whatever");
    }
    MicroInstruction mc;
    return mc;
}
