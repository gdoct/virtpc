#include "cpu.h"
#include "../microcode/microcode.h"
static Microcode s_microcode = Microcode::load();

Cpu::Cpu(Bus* cpubus, Clock* clock) {
    bus = cpubus;
    clock->registerCallback(std::bind(&Cpu::clocktick, this));
    memory.clear();
}

void Cpu::clocktick() {
    step();
}

Byte Cpu::get_x() { return x; }
void Cpu::set_x(Byte newx){ x = newx; }
Byte Cpu::get_y() { return y; }
void Cpu::set_y(Byte newy){ y = newy; }
Byte Cpu::get_acc() { return acc; }
void Cpu::set_acc(Byte newacc){ acc = newacc; }
Byte Cpu::get_pc() { return pc; }
void Cpu::set_pc(Byte newpc){ pc = newpc; }
Byte Cpu::get_status() { return status; }
void Cpu::set_status(Byte newstatus){ status = newstatus; }

Byte Cpu::fetch_next_byte() {
    auto data = memory.read_memory(pc);
    pc++;
    return data;
}

void Cpu::step() { 
    auto instruction = fetch_next_byte();
    auto opcode = OpcodeParser::parse(instruction);
    process_instruction(opcode);
 }

 void Cpu::process_instruction(Opcodes opcodes) {
    auto stepcount = s_microcode.get_step_count(opcodes);
    Log::trace("d");
    for (int c = 0; c < stepcount; c++) {
        auto step = s_microcode.get_step(opcodes, c);
        step.execute(this);
    }
 }
