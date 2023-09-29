#ifndef CPUSTATE_H
#define CPUSTATE_H
enum CpuState {
    idle,
    fetch,
    decode,
    execute,
    error
};

#endif