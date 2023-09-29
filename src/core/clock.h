#ifndef CLOCK_H
#define CLOCK_H
#include "bus.h"

#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>

class Clock {
public:

    typedef std::function<void()> Callback;
    void registerCallback(Callback callback);
    void start(int interval_ms);
    void stop();
    void step();
    
private:
    std::vector<Callback> callbacks;
    std::thread thread;
    bool running = false;
    void tick(int interval_ms);
};
#endif