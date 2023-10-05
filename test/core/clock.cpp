#include "clock.h"
#include "../../src/core/clock.h"

/*
class Clock {
    public:
        void registerCallback(const std::function<void()>& callback);
        void start(int interval_ms);
        void stop();
        void step() const;
};

*/
bool clock_canBeCreated() {
    Log::info("clock_canBeCreated");
    auto clock = new Clock();
    ASSERT(clock  != nullptr, "clock could not be created");
    return true;
}

bool clock_registercallback() {
    Log::info("clock_registercallback");
    int hitcount = 0;
    auto callback = [&hitcount] { hitcount += 1; };
    auto clock = new Clock();
    clock->registerCallback(callback);
    ASSERT(hitcount == 0, "hitcount should be 0 but was " + std::to_string(hitcount));
    clock->step();
    ASSERT(hitcount == 1, "hitcount should be 1 but was " + std::to_string(hitcount));
    return true;
}

bool clock_registercallback_threaded() {
    Log::info("clock_registercallback_threaded");
    int hitcount = 0;
    auto callback = [&hitcount] { hitcount += 1; };
    auto clock = new Clock();
    clock->registerCallback(callback);
    ASSERT(hitcount == 0, "hitcount should be 0 but was " + std::to_string(hitcount));
    clock->start(50);
    this_thread::sleep_for(std::chrono::seconds(1));
    clock->stop();
    ASSERT(hitcount > 18, "hitcount should be greater than 18 but was " + std::to_string(hitcount));
    return true;
}

bool clock_startstop_multiple() {
    Log::info("clock_startstop_multiple");
    int hitcount = 0;
    auto callback = [&hitcount] { hitcount += 1; };
    auto clock = new Clock();
    clock->registerCallback(callback);
    for (auto i = 0; i < 10; i++){
        clock->start(5);
        this_thread::sleep_for(std::chrono::milliseconds(50));
        clock->stop();
    }
    ASSERT(hitcount > 95, "hitcount should be greater than 95 but was " + std::to_string(hitcount));
    return true;
}

bool clock_startstop_shouldnothitwhilepaused() {
    int oldhitcount = 0;
    int hitcount = 0;
    auto callback = [&hitcount] { hitcount += 1; };
    auto clock = new Clock();
    clock->registerCallback(callback);
    for (auto i = 0; i < 10; i++){
        clock->start(5);
        this_thread::sleep_for(std::chrono::milliseconds(20));
        clock->stop();
        ASSERT(hitcount > oldhitcount, "hitcount was not increased while the clock was running");

        // there could be a trailing handler, give it 5ms to unwind
        // this_thread::sleep_for(std::chrono::milliseconds(5));
        oldhitcount = hitcount;

        this_thread::sleep_for(std::chrono::milliseconds(50));
        ASSERT(hitcount == oldhitcount, "hitcount was increased while the clock was stopped");
    }
    return true;
}

void ClockTests::register_tests() {
    UNIT_TEST(clock_canBeCreated);
    UNIT_TEST(clock_registercallback);
    UNIT_TEST(clock_registercallback_threaded);
    UNIT_TEST(clock_startstop_multiple);
    UNIT_TEST(clock_startstop_shouldnothitwhilepaused);
}
