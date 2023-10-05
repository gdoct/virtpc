#include "cpu.h"
#include "executionengine.h"

using namespace std;
const string MICROCODE_DAT_FILE = "microcode.dat";
std::unique_ptr<ExecutionEngine> engine;

Cpu::Cpu() : bus(new Bus()), 
             clock(new Clock()), 
             memory(new Memory()){
    memory->clear();
    if (engine == nullptr) {
        engine = ExecutionEngine::create(MICROCODE_DAT_FILE);
    }
    clock->registerCallback( [this] { this->clocktick(); } );
}

Cpu::Cpu(Bus* cpubus, Clock* clock,  Memory* memory) : bus(cpubus), clock(clock), memory(memory) {
    clock->registerCallback([this] { this->clocktick(); });
}

Cpu::Cpu(Cpu& other) : x(other.x), 
                       y(other.y), 
                       acc(other.acc), 
                       pc(other.pc), 
                       mc(other.mc), 
                       status(other.status),
                       bus(new Bus(*other.bus)),
                       clock(),
                       memory(new Memory(*other.memory)) {
    if (engine == nullptr) {
        engine = ExecutionEngine::create(MICROCODE_DAT_FILE);
    }
}

void Cpu::clocktick() {
    step();
}

Byte Cpu::get_x() const { return x; }
void Cpu::set_x(Byte newx){ x = newx; }
Byte Cpu::get_y() const { return y; }
void Cpu::set_y(Byte newy){ y = newy; }
Byte Cpu::get_acc() const { return acc; }
void Cpu::set_acc(Byte newacc){ acc = newacc; }
Word Cpu::get_pc() const { return pc; }
void Cpu::set_pc(Word newpc){ pc = newpc; }
Word Cpu::get_mc() const { return mc; }
void Cpu::set_mc(Word newmc){ mc = newmc; }
Byte Cpu::get_status() const { return status; }
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
    auto instruction = fetch_next_byte();
    auto opcode = OpcodeParser::parse(instruction);
    process_instruction(opcode);
 }

 void Cpu::process_instruction(Opcodes opcodes) const {
//    auto stepcount = _engine.get_step_count(opcodes);
    std::cout << "code: " << (Byte) opcodes << endl;
    // Log::trace("d");
    // for (int c = 0; c < stepcount; c++) {
    //     auto step = _engine.get_step(opcodes, c);
    //     step.execute(this);
    // }
 }
