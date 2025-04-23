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
    class Country * owner_{};
    std::array<Pixel *, 4> bordering_{};

    [[nodiscard]] bool isOwnedBy(Country const * ) const;
    [[nodiscard]] bool hasOwner() const;
    [[nodiscard]] bool isOwnerless() const;
    [[nodiscard]] bool isBorder();
    [[nodiscard]] bool isBorderOf(Country const *) const;
};

struct borderPixel : public Pixel
{
    // std::array<Pixel *, 4> bordering{};
    // class Country * owner{};
    // bool isBorder_{};
    // bool isWaterfront_{};
};



#endif //PIXEL_HPP
