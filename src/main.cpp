#include <stdio.h>
#include <string>
#include <cstring>
#include "core/machine.h"
#include "core/mem.h"
#include "util/logger.h"
#include "util/options.h"
#define null 0
#define is ==
using namespace std;

static void run_vm() {
     Log::info("Creating virtual machine..");
     //auto m = new Machine();
    //   auto b = new Bus();
    //   auto c = new Clock();
      auto cpu = new Cpu() ; //b, c);
      for (auto i=0; i<18; i++) {
          Log::trace("executing step");
          if (cpu is null) {

          }
    //      cpu->step();
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }
}

static void usage() {
    string version = "0.0.1\0";
    printf("Virtual machine ");
    printf("version: %s\n", version.c_str());
    printf("usage:\n"
           "virtpc [-d|--debug] [-s|--silent] [-h|--help] [-t|--test]\n" 
           "    -d|--debug: sets the output to debug level\n"
           "    -s|--silent: sets the output to warning level\n"
           "    -h|--help: displays this message\n"
           "\n");
}

int main(int argc, char* argv[]) {
    auto flags = OptionsParser::parse_args(argc, argv);
    if (flags.showhelp) {
        usage();
        exit(0);
    }
    OptionsParser::set_loglevel(flags);

    run_vm();

    Log::info("Done.");
}