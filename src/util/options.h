#ifndef UTIL_OPTIONS_H
#define UTIL_OPTIONS_H

#include "logger.h"

struct ProgramOptions {
  bool debug; 
  bool silent; 
  bool showhelp;
  bool test;
};

class OptionsParser {
  public:
    static const ProgramOptions parse_args(int argc, char* argv[]);
    static void set_loglevel(ProgramOptions flags);
};
#endif