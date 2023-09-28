#ifndef BUS_H
#define BUS_H

#include <iostream>
#include <vector>
#include <functional>

class Bus {
    public:
        void Tick()
        {
            for (auto callback : _callbacks) {
                callback();
            }
        }

    private:
        std::vector<std::function<void()>> _callbacks;
};

#endif