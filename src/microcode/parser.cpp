#include "parser.h"

static int convert_to_int16(std::string& step) {
    if (step.empty()) {
        return 0;
    }
    try {
        int16_t result = std::stoi(step, nullptr, 16);
        return result;
    }
    catch (int) {
    }
    return 0;
}

InstructionStep parse_line(std::istringstream& iss) {
    //try {
        //std::string opcode, hex, step, operation;
        //std::getline(iss, opcode, '|');
        //std::getline(iss, hex, '|');
        //std::getline(iss, step, '|');
        //std::getline(iss, operation, '|');
        //int16_t stepid = convert_to_int16(step);
        //int16_t key = convert_to_int16(hex);
        //std::cout << stepid << " ; " << key << std::endl;
        auto step = InstructionStep(1);
        return step;
//        return {key, opcode, stepid, operation};
    //} catch (int) {
  //      return {0xff, "Error", 0, ""}; 
    //}
}

std::unordered_map<Byte, std::unordered_map<int, InstructionStep>> Parser::read_microcode_table(std::string filename) {
    std::unordered_map<Byte, std::unordered_map<int, InstructionStep>> table;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        // Skip header line
        std::getline(file, line);

        while (std::getline(file, line)) {
            //std::istringstream iss(line);
            //auto operation = parse_line(iss);
            //table[operation.hex][operation.stepid] = operation;
        }
        file.close();
    } else {
        Log::error("Unable to open file with microcode instructions " + filename);
    }
    return table;
}