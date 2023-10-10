#include "cpu.h"
#include "executionengine.h"
#include "../api/constants.h"
//using namespace std;

Cpu::Cpu() : bus(new Bus()), 
             clock(new Clock()), 
             memory(new Memory()),
             engine(ExecutionEngine::create_execution_engine_ptr(Paths::get_path(MICROCODE_FILENAME))){
    memory->clear();
    clock->registerCallback( [this] { this->clocktick(); } );
}

Cpu::Cpu(Bus* cpubus, Clock* clock,  Memory* memory, ExecutionEngine* engine) : bus(cpubus), clock(clock), memory(memory), engine(engine) {
    clock->registerCallback([this] { this->clocktick(); });
}

Cpu::Cpu(Cpu& other) : x(other.x), 
                       y(other.y), 
                       acc(other.acc), 
                       pc(other.pc), 
                       mc(other.mc), 
                       status(other.status),
                       bus(new Bus(*other.bus)),
                       clock(new Clock()),
                       memory(new Memory(*other.memory)),
                       engine(new ExecutionEngine(*other.engine)) {
    clock->registerCallback( [this] { this->clocktick(); } );
}

// needed for the forward declaration
Cpu::~Cpu() = default;

void Cpu::clocktick() {
    step();
}

Byte Cpu::get_x() { return x; }
void Cpu::set_x(Byte newx){ x = newx; }
Byte Cpu::get_y() { return y; }
void Cpu::set_y(Byte newy){ y = newy; }
Byte Cpu::get_acc() { return acc; }
void Cpu::set_acc(Byte newacc){ acc = newacc; }
Word Cpu::get_pc() { return pc; }
void Cpu::set_pc(Word newpc){ pc = newpc; }
Word Cpu::get_mc() { return mc; }
void Cpu::set_mc(Word newmc){ mc = newmc; }
Byte Cpu::get_status() { return status; }
void Cpu::set_status(Byte newstatus){ status = newstatus; }

Byte Cpu::fetch_next_byte() {
    auto data = memory->read_byte(pc);
    pc += 1;
    return data;
}

Word Cpu::fetch_next_word() {
    auto word = memory->read_word(pc);
    pc += 2;
    return word;
}

void Cpu::step() { 
    engine->step(this);
 }

 void Cpu::process_instruction(Opcodes opcodes) const {
    std::cout << "code: " << (Byte) opcodes << std::endl;
 }
