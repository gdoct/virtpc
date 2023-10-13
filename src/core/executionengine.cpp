#include <vector>
#include "executionengine.h"
#include "../microcode/instructionstep.h"
#include "../api/numbers.h"

// minimum cycles for a given instruction is 2
//
// cycle 1 read memory at location of pc
// cycle 2 feed instruction to microcode
// rest is optional depending on cycles defined for the instruction in the microcode
void handleInterrupt() {
    throw std::bad_function_call();
}

void ExecutionEngine::step(Cpu* cpu) {
    if (cpu == nullptr) {
        throw std::invalid_argument("cpu");
    }

    switch (this->currentstep) {
        case 0: {
            // fetch
            if (is_interrupt_raised) {
                handleInterrupt();
            } else {
                auto mem = cpu->get_memory();
                std::string reg = "pc";
                Word pc = cpu->get_register_word(reg);
                Byte instr = mem->read_byte(pc);
                cpu->set_register_word(reg, pc + 1);
                this->currentinstruction = instr;
            }
            break;
        }
        case 1:
        {
            // decode
            auto& steps = this->microcode[this->currentinstruction];
            this->stepcount = steps.size() + 2;
            break;
        }
        default:
        {
            // execute
            size_t curstep = currentstep - 2;
            auto& mc = this->microcode[this->currentinstruction];
            if (mc.size() <= curstep) {
                // error
                if (mc.size() ==0) {
                    Log::error("no microcode defined for instruction " + std::to_string(this->currentinstruction));
                } else {
                    Log::error("insufficient microcode defined for instruction " + std::to_string(this->currentinstruction) + ", step "+ std::to_string(this->currentstep));
                }
                this->currentstep = 0;
                this->stepcount = 2;
                return;
            }

            for(auto& microstep : mc[curstep].expressions) {
                microstep->execute(cpu);
            }
            break;
        }
    }
    
    this->currentstep++;
    if (this->currentstep > stepcount) {
        this->currentstep = 0;
        this->stepcount = 2;
    }
}

void ExecutionEngine::raise_interrupt(Word isr_address) {
/**
 * An interrupt on a 6502 CPU can be broken down into the following micro steps:
    1. Interrupt Request (IRQ) or Non-Maskable Interrupt (NMI) Signal: The interrupt process begins when an IRQ or NMI signal is received1.
    2. Current Instruction Completion: The CPU completes the current instruction before responding to the interrupt1.
    3. Push Program Counter (PC) and Processor Status (P) to Stack: The PC and P are pushed onto the stack1. This allows the CPU to return to its previous state after servicing the interrupt.
    4. Set Interrupt Disable Flag: The interrupt disable flag in the status register is set1. This prevents further interrupts from being processed until the current one is serviced.
    5. Load New Program Counter (PC): The PC is loaded with the interrupt vector address1. This address points to the interrupt service routine, which is the code that will be executed in response to the interrupt.
    6. Execute Interrupt Service Routine (ISR): The ISR is executed2. This routine contains the code that responds to the interrupt, such as handling input/output operations or updating system timers.
    7. Pull Processor Status (P) and Program Counter (PC) from Stack: After the ISR is completed, the P and PC are pulled from the stack1. This restores the CPU to its state before the interrupt occurred.
    8. Return from Interrupt (RTI): The RTI instruction is executed2, signaling the end of the interrupt process. The CPU resumes executing instructions from where it left off before the interrupt occurred.
  Each of these steps occurs over one or more clock cycles, with some steps like executing the ISR potentially taking many cycles depending on the complexity of the routine2.
 * 
*/
    if (!this->is_interrupt_raised && !this->is_servicing_interrupt) {
        this->is_interrupt_raised = true;
        this->interrupt_address = isr_address;
    }
}

void ExecutionEngine::compile_microcode() {
    for(auto &instructions : microcode) {
        auto &steps = instructions.second;
        for (auto& step : steps) {
            step.second.compile();
        }
    }
}

ExecutionEngine* ExecutionEngine::create_execution_engine(const std::string& filename) {
    auto mc = Parser().read_microcode_table(filename);
    return new ExecutionEngine(mc);
}

std::unique_ptr<ExecutionEngine> ExecutionEngine::create_execution_engine_ptr(const std::string& filename) {
    auto mc = Parser().read_microcode_table(filename);
    return std::make_unique<ExecutionEngine>(mc);
}