#include <vector>
#include "executionengine.h"
#include "../microcode/instructionstep.h"
#include "../api/numbers.h"

void ExecutionEngine::step(Cpu* cpu) {
    if (cpu == nullptr) {
        throw std::invalid_argument("cpu");
    }

    switch (this->currentstep) {
        case 0: {
            // fetch
            auto mem = cpu->get_Memory();
            auto pc = cpu->get_pc();
            Byte instr = mem->read_byte(pc);
            cpu->set_pc(cpu->get_pc() + 1);
            this->currentinstruction = instr;
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
                Log::error("microcode error");
                this->currentstep = 0;
                this->stepcount = 2;
                return;
            }

            auto& operationnames = mc[curstep].expressionstrings;
            for(auto& opname : operationnames) {
                Log::info("   microstep for step " + std::to_string(this->currentstep) + " : " + opname);
            }
           // auto operation = StepExpression::compile(mc[curstep].operation, cpu);
           // operation->execute();
            break;
        }
    }
    
    this->currentstep++;
    if (this->currentstep > stepcount) {
        this->currentstep = 0;
        this->stepcount = 2;
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