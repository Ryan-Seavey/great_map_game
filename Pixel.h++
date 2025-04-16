//
// Created by diogenes on 4/3/25.
//

#ifndef PIXEL_HPP
#define PIXEL_HPP
#include <array>
#include <bitset>


struct Pixel {
    unsigned rgba_ = 0xFFFFFFFF;
    bool isBorder_{};
    bool isWaterfront_{};
    class Country * owner{};
    std::array<Pixel *, 4> bordering{};
};

struct borderPixel : public Pixel
{
    std::array<Pixel *, 4> bordering{};
    class Country * owner{};
    bool isBorder_{};
    bool isWaterfront_{};
};



#endif //PIXEL_HPP
