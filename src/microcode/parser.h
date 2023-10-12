#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "../core/opcodes.h"
#include "../util/logger.h"
#include "instructionstep.h"
#include "../api/constants.h"

/*
parses a file in this format:

OPCODE|HEX|STEP|[assigned [operand] assignee] [[ [separator] [assigned] [operand] [assignee] ]]
LDA|2A|1|;MC := PC
LDA|2A|2|;MC := MEM
LDA|2A|3|;A := MEM
...
BEQ|1A|1|;MC := PC
BEQ|1A|2|A == MEM;MC = PC
BEQ|1A|3|A == MEM;PC = MEM

*/

class Parser {
    public:
        std::unordered_map<Byte, std::unordered_map<int, InstructionStep>> read_microcode_table(std::string filename);
};

#endif