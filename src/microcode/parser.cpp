#include "parser.h"
#include "sstream"
#include <tuple>

static Byte convert_to_int8(std::string& step) {
    trim(step);
    if (step.empty()) {
        return 0;
    }
    try {
        int8_t result = std::stoi(step, nullptr, 8);
        return result;
    }
    catch (int) {
    }
    return 0;
}

static Word convert_hex_to_int16(std::string& step) {
    trim(step);
    if (step.empty()) {
        return 0;
    }
    Word value;
    std::stringstream ss;
    ss << std::hex << step;
    ss >> value;
    return value;
}

bool parse_line(std::istringstream& iss, InstructionStep& instructionstep) {

    std::string temp;
    // strip comments
    std::getline(iss, temp, ';');
    trim(temp);
    if (temp.empty()) {
        return false;
    }

    // get first arg (instruction)
    std::getline(iss, temp, '|');
    if (temp.empty())
    {
        return false;
    }
    instructionstep.instruction = convert_hex_to_int16(temp);

    // get second arg (step)
    std::getline(iss, temp, '|');
    if (temp.empty())
    {
        return false;
    }
    instructionstep.stepid = convert_to_int8(temp);

    // Parse instructions
    while (std::getline(iss, temp, '|')) {
        trim(temp);
        if (!temp.empty())
        {
            instructionstep.expressionstrings.push_back(temp);
        }
    }

    return (instructionstep.expressionstrings.size() > 0);
}

std::unordered_map<Byte, std::unordered_map<int, InstructionStep>> Parser::read_microcode_table(std::string filename) {
    std::unordered_map<Byte, std::unordered_map<int, InstructionStep>> table;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        // Skip header line
        std::getline(file, line);

        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            std::istringstream iss(line); 
            InstructionStep instructionstep;
            auto is_valid = parse_line(iss, instructionstep);
            if (is_valid) {
                table[instructionstep.instruction][instructionstep.stepid] = instructionstep;
            }
            else Log::error("invalid line in microcode " + line);
        }
        file.close();
    } else {
        Log::error("Unable to open file with microcode instructions " + filename);
    }
    return table;
}