#include "constants.h"
#include "../util/logger.h"
#include <iostream>
#include <stdlib.h>
#include <string>

//using namespace std;

static std::string rootpath = "";

static std::string combine_paths(std::string path1, std::string path2) {
#ifdef _MSC_VER
    return path1 + "..\\..\\" + path2;
#else
    return path1 + "/" + path2;
#endif
}

void Paths::set_rootpath(std::string newrootpath) {
    rootpath = newrootpath;
}

std::string Paths::get_path(std::string relpath) {
    auto result = combine_paths(rootpath, relpath);
    return result;
}

