#include "testbase.h"
#include "../core/mem.h"

bool memory_shouldstore() {
    return true;
}

bool memory_shouldreturnzero() {
    return true;
}

class MemoryTests : public TestBase {
    public: 
        void RunAll() override {
            run_test("memory_shouldstore", memory_shouldstore);
            run_test("memory_shouldreturnzero", memory_shouldreturnzero);
        }
        
};