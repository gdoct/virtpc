#include "bus.h"

void Bus::Tick() const {
    for (const auto callback : _callbacks) {
        callback();
    }
}