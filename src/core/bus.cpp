#include "bus.h"

void Bus::Tick() {
    for (auto callback : _callbacks) {
        callback();
    }
}