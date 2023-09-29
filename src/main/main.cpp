#include <stdio.h>
#include <cstring>
#include "../core/machine.h"
#include "../util/logger.h"
#include "../util/options.h"

void run_vm() {
    Log::info("Creating virtual machine..");
    Machine* m = new Machine();
    for (int i=0; i<18; i++) {
        m->Step();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    delete m;
}

void usage() {
    string version = "0.0.1\0";
    printf("Virtual machine ");
    printf("version: %s\n", version.c_str());
    printf("usage:\n"
           "virtpc [-d|--debug] [-s|--silent] [-h]\n" 
           "    -d|--debug: sets the output to debug level\n"
           "    -s|--silent: sets the output to warning level\n"
           "    -h|--help: displays this message\n"
           "\n");
}

int main(int argc, char* argv[]) {
    ProgramOptions flags = OptionsParser::parse_args(argc, argv);
    if (flags.showhelp) {
        usage();
        exit(1);
    }
    OptionsParser::set_loglevel(flags);
    run_vm();
    Log::info("Done.");
}