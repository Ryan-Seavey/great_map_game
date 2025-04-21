//
// Created by diogenes on 4/16/25.
//

#ifndef RYUTIL_H
#define RYUTIL_H
#include <optional>
#include <random>

namespace RyUtil
{
    constexpr unsigned operator""_rgba(unsigned long long rgba) {
        if constexpr (std::endian::native == std::endian::big) return rgba;
        else return
               ((rgba & 0x000000FFu) << 24) | // R → shift to byte 3 (MSB)
               ((rgba & 0x0000FF00u) << 8)  | // G → byte 2
               ((rgba & 0x00FF0000u) >> 8)  | // B → byte 1
               ((rgba & 0xFF000000u) >> 24); // A → byte 0 (LSB)
    }


    template<typename T = unsigned>
    T randint(T min, T max) requires std::is_integral_v<T>
    {
        if (min > max) std::swap(min, max);
        static std::random_device rd;
        static std::mt19937 twister_engine{rd()};
        std::uniform_int_distribution<T> dist{min, max};
        return dist(twister_engine);
    }

    template<typename T = unsigned>
    consteval T compilerand(T min, T max) requires std::is_integral_v<T>
    {
        return 0;
    }

    template<typename T = double>
    T randfloat(T min, T max) requires std::is_floating_point_v<T>
    {
        static std::random_device rd;
        static std::mt19937 twister_engine{rd()};
        static std::uniform_real_distribution<T> dist{min, max};
        return dist(twister_engine);
    }

    template<typename T,class D =
    std::conditional_t<std::is_floating_point_v<T>, std::uniform_real_distribution<T>,std::uniform_int_distribution<T>>>
    T random(T min, T max, std::optional<D> dist = std::nullopt) requires std::is_arithmetic_v<T>
    {
        if (min > max) std::swap(min, max);
        thread_local std::random_device rd;
        thread_local std::mt19937 twister_engine{rd()};
        if (dist) return (*dist)(twister_engine);
        return D{min, max}(twister_engine);
    }

    enum Directions
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        W = UP,
        S,
        A,
        D,
        NORTH = UP,
        SOUTH,
        WEST,
        EAST
    };



}


#endif //RYUTIL_H
