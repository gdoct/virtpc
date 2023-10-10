#include "options.h"

const ProgramOptions OptionsParser::parse_args(int argc, char *argv[]) {
    auto flags = ProgramOptions();
    flags.debug = false;
    flags.silent = false;
    flags.showhelp = false;
    flags.test = false;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg[0] == '-')
        {
            if (arg == "-d" || arg == "--debug") {
                flags.debug = true;
            }
            else if (arg == "-t" || arg == "--test") {
                flags.test = true;
            }
            else if (arg == "-s" || arg == "--silent") {
                flags.silent = true;
            }
            else if (arg == "-h" || arg == "--help") {
                flags.showhelp = true;
            }
            else {
                Log::warn("Invalid flag: " + arg);
                flags.showhelp = true;
            }
        }
        else {
            Log::warn("Invalid argument: " + arg);
            flags.showhelp = true;
        }
    }
    return flags;
}

void OptionsParser::set_loglevel(ProgramOptions flags) {
    if (flags.silent) {
        Log::set_LogLevel(LogLevel::Warning);
    }
    else if (flags.debug) {
        Log::set_LogLevel(LogLevel::Trace);
    }
    else {
        Log::set_LogLevel(LogLevel::Information);
    }
}