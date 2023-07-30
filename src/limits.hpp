#pragma once

#include <atomic>
#include <cstdint>

#include "types.hpp"

namespace Search {
    struct Limits {
        Value score = VALUE_NONE;
        Depth depth = 0;

        std::atomic<uint64_t> nodes = false;

        std::atomic<bool> timeset = false;
        std::atomic<bool> stopped = false;
        std::atomic<bool> nodeset = false;
        std::atomic<bool> uci = false;
    };
}