#ifndef MICROCODE_H
#define MICROCODE_H

#include "microinstruction.h"
#include "../core/opcodes.h"

class Microcode {
    public:
        static const Microcode load();
        Microcode();
        int get_step_count(Opcodes instruction) const;
        MicroInstruction get_step(Opcodes instruction, int step) const;
};

#endif