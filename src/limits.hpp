#pragma once

#include <atomic>
#include <cstdint>

namespace Search {
    struct Limits {
        int32_t score = 0;
        uint8_t depth = 0;

        std::atomic<uint64_t> nodes = false;

        std::atomic<bool> timeset = false;
        std::atomic<bool> stopped = false;
        std::atomic<bool> nodeset = false;
        std::atomic<bool> uci = false;
    };
}