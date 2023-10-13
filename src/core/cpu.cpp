#include "cpu.h"
#include "executionengine.h"
#include "../api/constants.h"
//using namespace std;

Cpu::Cpu() : clock(new Clock()), 
             memory(new Memory()),
             engine(ExecutionEngine::create_execution_engine(Paths::get_path(MICROCODE_FILENAME))){
    memory->clear();
    clock->registerCallback( [this] { this->clocktick(); } );
}

Cpu::Cpu(Clock* clock,  Memory* memory, ExecutionEngine* engine) : clock(clock), memory(memory), engine(engine) {
    clock->registerCallback([this] { this->clocktick(); });
}

Cpu::Cpu(Cpu& other) : clock(new Clock()),
                       memory(new Memory(*other.memory)),
                       engine(new ExecutionEngine(*other.engine)) {
    clock->registerCallback( [this] { this->clocktick(); } );
}

// needed for the forward declaration
Cpu::~Cpu() = default;

void Cpu::clocktick() {
    step();
}

Byte Cpu::get_register(const std::string& name) { 
    std::string name_lower = toLowerCase(name);
    if (registers.count(name_lower)== 0) {
       throw std::invalid_argument(name);
    }
    return registers[name_lower]; 
}

Word Cpu::get_register_word(const std::string& name) { 
    std::string name_lower = toLowerCase(name);
    if (registers.count(name_lower + "_low")== 0 || registers.count(name_lower + "_high")== 0) {
        if (registers.count(name_lower) == 0)
            throw std::invalid_argument(name);
        return (Word) registers[name_lower];
    } else {
        Byte high_byte = registers[name_lower + "_high"];
        Byte low_byte = registers[name_lower + "_low"];
        return high_byte << 8 | low_byte;
    }
}

void Cpu::set_register(const std::string& name, Byte newx) {
    std::string name_lower = toLowerCase(name);
    if (registers.count(name_lower)== 0) {
        throw std::invalid_argument(name);
    }
    registers[name_lower] = newx; 
 }

void Cpu::set_register_word(const std::string& name, Word value) {
    std::string name_lower = toLowerCase(name);
    if (registers.count(name_lower + "_low")== 0 || registers.count(name_lower + "_high")== 0) {
        if (registers.count(name_lower) == 0)
            throw std::invalid_argument(name);
        registers[name_lower] = value & 0xFF;
    } else {
        uint8_t high_byte = (value >> 8) & 0xFF; // shift right by 8 bits to get the high byte
        uint8_t low_byte = value & 0xFF;
        registers[name_lower + "_low"] = low_byte;
        registers[name_lower + "_high"] = high_byte;
    }
 }

void Cpu::step() { 
    engine->step(this);
}