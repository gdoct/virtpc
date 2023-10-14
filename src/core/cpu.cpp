#include "cpu.h"
#include "executionengine.h"
#include "../api/constants.h"

// -------------------------------------- constructors --------------------------------------
// constructor definition in this cpp file is required for the forward declaration
// to make the circular reference work with the execution engine
Cpu::~Cpu() = default;

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

// -------------------------------------- general functions --------------------------------------

void Cpu::step() { 
    engine->step(this);
}

void Cpu::clocktick() {
    step();
}

// -------------------------------------- register operations --------------------------------------
Byte Cpu::get_register(const std::string& name) { 
    std::string name_lower = to_lower(name);
    if (registers.count(name_lower)== 0) {
       throw std::invalid_argument(name);
    }
    return registers[name_lower]; 
}

Word Cpu::get_register_word(const std::string& name) { 
    std::string name_lower = to_lower(name);
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
    std::string name_lower = to_lower(name);
    if (registers.count(name_lower)== 0) {
        throw std::invalid_argument(name);
    }
    registers[name_lower] = newx; 
 }

void Cpu::set_register_word(const std::string& name, Word value) {
    std::string name_lower = to_lower(name);
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

// -------------------------------------- stack operations --------------------------------------
void increase_stack_pointer(std::map<std::string, Byte>& registers) {
    auto stackpointer = registers["sp"];
    if (stackpointer == 0xff) stackpointer = 0x00; else stackpointer++;
    registers["sp"] = stackpointer;
}

void decrease_stack_pointer(std::map<std::string, Byte>& registers) {
    auto stackpointer = registers["sp"];
    if (stackpointer == 0x00) {
        throw std::overflow_error("stack overflow");
    } else stackpointer--;
    registers["sp"] = stackpointer;
}

void Cpu::push_stack(Byte value) {
    decrease_stack_pointer(registers);
    auto address = 0x0100 | registers["sp"];
    memory->write(address, value);
}

void Cpu::push_stack(Word value) {
    Byte high_byte = value >> 8;
    Byte low_byte = value & 0xFF;
    push_stack(high_byte);
    push_stack(low_byte);
}

Byte Cpu::pop_stack_byte() {
    increase_stack_pointer(registers);
    auto address = 0x0100 | registers["sp"];
    return memory->read_byte(address);
}

Word Cpu::pop_stack_word() {
    Byte low_byte = pop_stack_byte();
    Byte high_byte = pop_stack_byte();
    return (high_byte << 8) | low_byte;
}

// -------------------------------------- status register operations --------------------------------------
void Cpu::set_status(const Byte& state_to_add) {
    this->registers["sp"] |= state_to_add;
}

bool Cpu::has_status(const Byte& state) {
    return (this->registers["sp"] & state) != 0;
}

void Cpu::clear_status(const Byte& state_to_remove) {
    this->registers["sp"] &= ~state_to_remove;
}