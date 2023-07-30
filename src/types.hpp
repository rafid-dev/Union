#pragma once

#include "chess.hpp"

#define NAME "Union"
#define AUTHOR "Rafid Ahsan"


// Type aliases.
using Depth = int;
using Value = int;
using Time = double;

constexpr Depth DEPTH_MAX = 63;
constexpr Depth DEPTH_MAX_PLY = 63;

constexpr Value VALUE_IS_MATE = 30000;
constexpr Value VALUE_IS_MATED = -VALUE_IS_MATE;
constexpr Value VALUE_KNOWN_WIN = 10000;
constexpr Value VALUE_IS_MATE_IN_MAX_PLY = (VALUE_IS_MATE - DEPTH_MAX_PLY);
constexpr Value VALUE_IS_MATED_IN_MAX_PLY = -VALUE_IS_MATE_IN_MAX_PLY;
constexpr Value VALUE_INFINITE = 30001;
constexpr Value VALUE_NONE = 32002;

constexpr Time TIME_UNSET = -1;