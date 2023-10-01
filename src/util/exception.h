#include <string>
using namespace std;

class Exception {
    public:
        virtual const string get_name() = 0;
};

class StackOverFlowException : public Exception {
    public:
        const string get_name() override { return "stack overflow"; }
};

class InvalidAccessException : public Exception {
    public:
        const string get_name() override { return "invalid address"; }
};