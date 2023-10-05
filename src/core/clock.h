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
    void registerCallback(const std::function<void()>& callback);
    void start(int interval_ms);
    void stop();
    void step() const;
    
private:
    std::vector<std::function<void()>> callbacks = std::vector<std::function<void()>>();
    std::jthread thread;
    bool running = false;
    int current_timeout;
    void tick(int interval_ms) const;
};
#endif