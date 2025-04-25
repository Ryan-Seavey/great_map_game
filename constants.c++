//
// Created by diogenes on 4/23/25.
//
#ifndef CONSTANTS_CPP_FUNNY
#define CONSTANTS_CPP_FUNNY
#include <chrono>
inline constexpr unsigned MAP_HEIGHT{75};
inline constexpr unsigned MAP_WIDTH{100};
inline constexpr unsigned MAP_AREA{MAP_WIDTH*MAP_HEIGHT};

namespace ticks
{
    inline constexpr unsigned TICKS_PER_DAY = 24;
    inline constexpr unsigned TICKS_PER_MONTH = TICKS_PER_DAY * 30;
    inline constexpr unsigned TICKS_PER_YEAR = TICKS_PER_MONTH * 12;
    inline float TICK_DURATION_SECONDS = 0.70f; // 50 ms = 20 ticks per second, LIKE MINCERAFT1?!?
    inline float tick_accumulator = 0.0f;
    inline uint64_t GLOBAL_TICK = 0;


    inline std::string toDate(const unsigned tick = GLOBAL_TICK)
    {
        std::stringstream ss;
        unsigned year = GLOBAL_TICK/TICKS_PER_YEAR;
        unsigned month = GLOBAL_TICK % TICKS_PER_YEAR / TICKS_PER_MONTH;
        unsigned day = GLOBAL_TICK % TICKS_PER_YEAR  % TICKS_PER_MONTH / TICKS_PER_DAY;
        unsigned seconds = tick % TICKS_PER_DAY;
        ss << month << "/" << day << "/" << year << " " << seconds;
        return ss.str();
    }
}

inline std::chrono::steady_clock::time_point last_frame_time = std::chrono::steady_clock::now();
#endif