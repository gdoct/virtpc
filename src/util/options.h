#ifndef OPTIONS_H
#define OPTIONS_H

#include "logger.h"

struct ProgramOptions {
  bool debug; 
  bool silent; 
  bool showhelp;
};

static const ProgramOptions options_parse_args(int argc, char* argv[]) {
  ProgramOptions flags;
  flags.debug = false;
  flags.silent = false;
  flags.showhelp = false;

  for (int i = 1; i < argc; i++) {
    string arg = argv[i];
    if (arg[0] == '-') {
      if (arg == "-d" || arg == "--debug") {
        flags.debug = true;
      }
      else if (arg == "-s" || arg == "--silent") {
        flags.silent = true;
      }
      else if (arg == "-h" || arg == "--help") {
        flags.showhelp = true;
      }
      else {
        Log::warn("Invalid flag: " + arg );
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

static void options_set_loglevel(ProgramOptions flags) {
    if (flags.silent) {
        Log::set_LogLevel(LogLevel::Warning);
    } else if (flags.debug) {
        Log::set_LogLevel(LogLevel::Trace);
    } else {
        Log::set_LogLevel(LogLevel::Information);
    }
}

#endif