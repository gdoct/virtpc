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
    // The callback function type
    typedef std::function<void()> Callback;

    // Register a callback
    void registerCallback(Callback callback);

    // Start the clock
    void start(int interval_ms);

    // Stop the clock
    void stop();

    // single clock step
    void step();
    
private:
    std::vector<Callback> callbacks;
    std::thread thread;
    bool running = false;

    // The tick function
    void tick(int interval_ms);
};
#endif