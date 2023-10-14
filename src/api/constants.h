#ifndef API_CONSTANTS_H
#define API_CONSTANTS_H
#include <string>

#ifdef _MSC_VER

const std::string MICROCODE_FILENAME = "rom\\microcode.dat";
const std::string C64_BASIC_KERNAL_FILENAME = "rom\\c64\\64c.251913-01.bin";
const std::string C64_CHARACTERGEN_FILENAME = "rom\\c64\\characters.901225-01.bin";

#else

const std::string MICROCODE_FILENAME = "rom/microcode.dat";
const std::string C64_BASIC_KERNAL_FILENAME = "rom/c64/64c.251913-01.bin";
const std::string C64_CHARACTERGEN_FILENAME = "rom/c64/characters.901225-01.bin";

#endif

class Paths {
    public:
        static void set_rootpath(std::string newrootpath);
        static std::string get_path(std::string relpath);
};

#endif