#include <stdio.h>
#include <cstring>
#include "../core/machine.h"
#include "../core/mem.h"
#include "../util/logger.h"
#include "../util/options.h"
#include "../test/testrunner.h"

void run_vm() {
    Log::info("Creating virtual machine..");
    auto m = new Machine();
    for (auto i=0; i<18; i++) {
        Log::trace("executing step");
        m->Step();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    auto mem = m->GetCpu()->memory;
    string s = "mem.dat";
    mem->dump(s);
    delete m;
}

void test_vm() {
    TestRunner::run_all_tests();
}

void usage() {
    string version = "0.0.1\0";
    printf("Virtual machine ");
    printf("version: %s\n", version.c_str());
    printf("usage:\n"
           "virtpc [-d|--debug] [-s|--silent] [-h|--help] [-t|--test]\n" 
           "    -d|--debug: sets the output to debug level\n"
           "    -s|--silent: sets the output to warning level\n"
           "    -t|--test: run all unit tests\n"
           "    -h|--help: displays this message\n"
           "\n");
}

int main(int argc, char* argv[]) {
    auto flags = OptionsParser::parse_args(argc, argv);
    if (flags.showhelp) {
        usage();
        exit(1);
    }
    OptionsParser::set_loglevel(flags);

    if (flags.test) {
        test_vm();
    } else {
        run_vm();
    }
    Log::info("Done.");
}