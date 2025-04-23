//
// Created by diogenes on 4/23/25.
//
#include "Pixel.h++"

#include <algorithm>


bool Pixel::isOwnedBy(Country const * const c) const
{
    return c == owner_;
}

bool Pixel::hasOwner() const
{
    return owner_ != nullptr;
}

bool Pixel::isOwnerless() const
{
    return owner_ == nullptr;
}

bool Pixel::isBorder() const
{
    return std::ranges::any_of(bordering_, [this](Pixel * i)
    {
        return i->owner_ != owner_;
    });
}

bool Pixel::isBorderOf(Country const * const c) const
{
    return std::ranges::any_of(bordering_, [c](Pixel * i)
    {
        return c == i->owner_;
    });
}
