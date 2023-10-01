#ifndef MICROINSTR_H
#define MICROINSTR_H

#include <stdio.h>
#include <cstring>
#include "../core/cpu.h"
#include "../util/logger.h"

class MicroInstruction {
    public:
        static MicroInstruction parse(string* data);
        void execute(const Cpu* cpu) const;
};

#endif