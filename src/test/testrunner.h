#include "memorytests.h"

class TestRunner {
    public:
        static void run_all_tests() {
            MemoryTests mt;
            mt.RunAll();
        };
};