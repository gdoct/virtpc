#include "testbase.h"

TestRunResult TestBase::RunAll() {
    TestRunResult tr = TestRunResult();
    return tr;
}

bool TestBase::run_test(string name, bool (*action)()) {
    try {
        auto result = action();
        if (result) {
            cout << "\033[32m[PASS] \033[0m" << name << endl;
        } else {
            cout << "\033[31m[FAIL] \033[0m"<< name << endl;
        }
        return result;
    } catch(int exception) { 
        /* .. */ 
        cout << "\033[31m[CRASH] " << name << "\033[0m" << endl;
    }
    return false;
}
