#ifndef CPUSTATE_H
#define CPUSTATE_H
enum class CpuState {
    idle,
    fetch,
    decode,
    execute,
    error
};

#endif