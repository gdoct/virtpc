#include "clock.h"
#include "bus.h"
#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>

using namespace std;

Clock::Clock() {}

Clock::Clock(Clock& other) : callbacks(other.callbacks), running(other.running) {

}

void Clock::registerCallback(const Callback& callback) {
    callbacks.push_back(callback);
}

// Start the clock
void Clock::start(int interval_ms) {
    running = true;
    thread = std::thread(&Clock::tick, this, interval_ms);
}

// Stop the clock
void Clock::stop() {
    running = false;
    if (thread.joinable()) {
        thread.join();
    }
}

void Clock::tick(int interval_ms) const {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
        for (const auto &callback : callbacks) {
            callback();
        }
    }
}

void Clock::step() const {
    for (const auto &callback : callbacks) {
        callback();
    }
}