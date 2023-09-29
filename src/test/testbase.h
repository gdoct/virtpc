#ifndef TESTBASE_H
#define TESTBASE_H

#include "../util/logger.h"

class TestBase {
    public:
        virtual void RunAll();
    protected:
        void run_test(char* name, bool (*action)()) {
            cout << "Running: " << name;
            auto result = action();
            cout << result ? "pass\n" : "fail\n";
        }
};

#endif