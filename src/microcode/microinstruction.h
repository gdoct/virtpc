#ifndef MICROINSTR_H
#define MICROINSTR_H

#include <stdio.h>
#include <string>
#include "../core/cpu.h"
#include "../util/logger.h"

class MicroInstruction {
    public:
        static MicroInstruction parse(std::string* data);
        void execute(const Cpu* cpu) const;
};

#endif