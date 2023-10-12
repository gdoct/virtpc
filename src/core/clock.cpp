#include "clock.h"
#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>

//using namespace std;

void Clock::registerCallback(const std::function<void()>& callback) {
    this->callbacks.push_back(callback);
}

// Start the clock
void Clock::start(int interval_ms) {
    this->running = true;
    current_timeout = interval_ms;
    this->thread = std::jthread([this, interval_ms] { this->tick(interval_ms); });
}

// Stop the clock
void Clock::stop() {
    this->running = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(current_timeout));
}

void Clock::tick(int interval_ms) const {
    while (this->running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
        for (const auto &callback : this->callbacks) {
            callback();
        }
    }
}

void Clock::step() const {
    for (const auto &callback : this->callbacks) {
        callback();
    }
}