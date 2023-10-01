#ifndef MICROINSTR_H
#define MICROINSTR_H

#include <stdio.h>
#include <cstring>
#include "../core/cpu.h"
#include "../util/logger.h"

class MicroInstruction {
    public:
        const static MicroInstruction parse(string* data);
        void execute(Cpu* cpu) const;
};

#endif