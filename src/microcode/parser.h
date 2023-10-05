#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "../core/opcodes.h"
#include "../util/logger.h"

/*
parses a file in this format:

OPCODE|HEX|STEP|OPERATION
LDA|2A|1|MEM_AT_PC > MC
LDA|2A|2|MEM_AT_MC > A
STA|2F|1|MEM_AT_PC > MC
STA|2F|2|A > MEM_AT_MC
...

*/

class Parser {
    public:
        std::unordered_map<Opcodes, std::unordered_map<int, std::string>> read_microcode_table(std::string filename);
};