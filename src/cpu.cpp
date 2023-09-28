#include "cpu.h"

Cpu::Cpu(Bus* cpubus, Clock* clock) {
    bus = cpubus;
    clock->registerCallback(std::bind(&Cpu::clocktick, this));
    state = CpuState::idle;
    statestep = 0;
}

void Cpu::clocktick()
{
    switch(state) {
        case CpuState::idle: 
        case CpuState::execute: 
            fetch();
            break;
        case CpuState::fetch: 
            decode();
            break;
        case CpuState::decode: 
            execute();
            break;
        case CpuState::error:
        default:
            Log::error("invalid cpu state, please reset the machine");
            break;
    }
}

word Cpu::get_x(){ return x; }
void Cpu::set_x(word newx){ x = newx; }
word Cpu::get_y(){ return y; }
void Cpu::set_y(word newy){ y = newy; }
word Cpu::get_acc(){ return acc; }
void Cpu::set_acc(word newacc){ acc = newacc; }
word Cpu::get_pc(){ return pc; }
void Cpu::set_pc(word newpc){ pc = newpc; }
word Cpu::get_status(){ return status; }
void Cpu::set_status(word newstatus){ status = newstatus; }

void Cpu::fetch(){ 
    Log::trace("fetch");
    state = CpuState::fetch;
 }

void Cpu::decode(){ 
    Log::trace("decode");
    state = CpuState::decode;
 }
void Cpu::execute(){      
    Log::trace("execute");
    state = CpuState::execute;
}
