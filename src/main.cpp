#include <stdio.h>
#include <cstring>
#include "machine.h"
#include "logger.h"
#include "options.h"

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
    ProgramOptions flags = options_parse_args(argc, argv);
    if (flags.help) {
        usage();
        exit(1);
    }
    options_set_loglevel(flags);
    run_vm();
    Log::info("Done.");
}