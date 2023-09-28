#include "clock.h"
#include "bus.h"
#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>
#include <stdio.h>

void Clock::registerCallback(Callback callback)
{
    callbacks.push_back(callback);
}

// Start the clock
void Clock::start(int interval_ms)
{
    running = true;
    thread = std::thread(&Clock::tick, this, interval_ms);
}

// Stop the clock
void Clock::stop()
{
    running = false;
    if (thread.joinable())
    {
        thread.join();
    }
}

void Clock::tick(int interval_ms)
{
    while (running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
        for (auto &callback : callbacks)
        {
            callback();
        }
    }
}

void Clock::step()
{
    for (auto &callback : callbacks)
    {
        callback();
    }
}