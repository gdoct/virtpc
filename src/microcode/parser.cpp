#include "parser.h"
struct Operation {
    int16_t hex;
    std::string opcode;
    int16_t stepid;
    std::string operation;
};

Operation parse_line(std::istringstream& iss) {
    try {
        std::string opcode, hex, step, operation;
        std::getline(iss, opcode, '|');
        std::getline(iss, hex, '|');
        std::getline(iss, step, '|');
        std::getline(iss, operation, '|');
        int16_t stepid = std::stoi(step, nullptr, 16);
        int16_t key = std::stoi(hex, nullptr, 16);
        return {key, opcode, stepid, operation};
    } catch (int) {
        return {0xff, "Error", 0, ""}; 
    }
}

std::unordered_map<Opcodes, std::unordered_map<int, std::string>> Parser::read_microcode_table(std::string filename) {
    std::unordered_map<Opcodes, std::unordered_map<int, std::string>> table;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        // Skip header line
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            auto operation = parse_line(iss);
            auto op = OpcodeParser::parse(operation.hex);
            if (op == Opcodes::E_NOT_IMPL) {
                Log::error("invalid opcode in microcode table : " + line);
            } else {
                table[op][operation.stepid] = operation.operation;
            }
        }
        file.close();
    } else {
        Log::error("Unable to open file with microcode instructions " + filename);
    }
    return table;
}