#ifndef CLOCK_H
#define CLOCK_H
#include "bus.h"

#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>

using Callback = std::function<void()>;

class Clock {
public:

    void registerCallback(const Callback& callback);
    void start(int interval_ms);
    void stop();
    void step() const;
    
private:
    std::vector<Callback> callbacks;
    std::thread thread;
    bool running = false;
    void tick(int interval_ms) const;
};
#endif