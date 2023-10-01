#include "microcode.h"
#include <string>

//const auto microcode = "";
/*
LDA
load word address parameter into mc
load memory into accum

STA
load word address parameter into mc
store accum into memory
*/
const Microcode Microcode::load() {
    Microcode mc;
    return mc;
}

int Microcode::get_step_count(Opcodes instruction) {
    if (instruction >= 1)
        return 0;
    else 
        return instruction;
}

MicroInstruction Microcode::get_step(Opcodes instruction, int step) {
    if (step > 0) {
        auto p = step % instruction;
        if (p > 0) Log::error("whatever");
    }
    MicroInstruction mc;
    return mc;
}

Microcode::Microcode() {

}