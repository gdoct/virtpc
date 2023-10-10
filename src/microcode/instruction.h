#ifndef INSTRUCTION_H
#define INSTRUCTION_H
struct Instruction {
    int16_t hex;
    std::string opcode;
    int16_t stepid;
    std::string operation;
};

#endif
