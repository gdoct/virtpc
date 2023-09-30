#ifndef BUS_H
#define BUS_H

#include <iostream>
#include <vector>
#include <functional>

class Bus {
    public:
        void Tick();

    private:
        std::vector<std::function<void()>> _callbacks;
};

#endif