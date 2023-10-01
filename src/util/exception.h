#include <string>

class Exception {
    public:
        virtual std::string get_name() const = 0;
};

class StackOverFlowException : public Exception {
    public:
        std::string get_name() const override { return "stack overflow"; }
};

class InvalidAccessException : public Exception {
    public:
        std::string get_name() const override { return "invalid address"; }
};