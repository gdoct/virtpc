#include <stdio.h>
#include <string>
#include <cstring>
#include "api/constants.h"
#include "core/machine.h"
#include "core/mem.h"
#include "util/logger.h"
#include "util/options.h"
#include <filesystem>
#ifdef _MSC_VER
#include "windows.h"
#else
#include <libgen.h>
#endif

static void run_vm() {
     Log::info("Creating virtual machine..");
     //auto m = new Machine();
    //   auto b = new Bus();
    //   auto c = new Clock();
      auto cpu = new Cpu() ; //b, c);

    //cpu->get_Memory()->

      for (auto i=0; i<18; i++) {
          Log::trace("executing step");
// 1. load rom "roms/c64/64c.251913-01.bin" at address $e000
// 2. load address stored at $fffd $fffc into program counter
// 3. go!
          cpu->step();
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }
}

static void usage() {
    std::string version = "0.0.1\0";
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
#ifdef _MSC_VER
    std::vector<char> executablePath(MAX_PATH);
    DWORD pathLength = GetModuleFileName(NULL, &executablePath[0], executablePath.size());
    if (pathLength == 0) {
        std::cerr << "Error getting executable path" << std::endl;
        return 1;
    }
    std::string fullPath(executablePath.begin(), executablePath.begin() + pathLength);
    std::filesystem::path directory_path(fullPath);
    auto result = directory_path.remove_filename();
    Paths::set_rootpath(result.string());
#else
    char full_path[4096];
    if (realpath(argv[0], full_path) != NULL) {
        std::string executable_path(full_path);
        char* path = dirname(&executable_path[0]);
        std::string directory_path(path);
        Paths::set_rootpath(directory_path);
    }
#endif
    auto flags = OptionsParser::parse_args(argc, argv);
    if (flags.showhelp) {
        usage();
        exit(0);
    }
    OptionsParser::set_loglevel(flags);

    run_vm();

    Log::info("Done.");
}