//
// Created by diogenes on 4/21/25.
//
#include "Country.h++"

#include <format>
#include <iostream>
#include <stdexcept>
#include <sstream>

inline std::ostream& resetTermColor(std::ostream& os) {
    return os << "\033[0m";
}

Country::Country(std::string name, unsigned color): name_{std::move(name)}, rgba_{color}
{}

Country::Country(std::string name, unsigned color, AI_module* ai): name_{std::move(name)}, rgba_{color}, brain{ai}
{}

Country::Country(unsigned color): rgba_{color}
{}


void Country::setOwnership(Pixel* ownee){
    setOwnership(this, ownee);
}

void Country::update() {
    brain->attemptExpansion(*this);
    brain->manageEconomy(*this);
    brain->performDiplomacy(*this);
}

Country::~Country(){
    if (ownedTiles_.empty()) return;
    for (auto & i : ownedTiles_)
    {
        i->owner_ = nullptr;
    }
    delete brain;
}

bool Country::atWar(Country* owner) const
{
    return atWar(this, owner);
}

void Country::makeWar(Country* c)
{
    makeWar(this, c);
}

void Country::makePeace(Country* c)
{
    makePeace(this, c);
}

void Country::updateBorders()
{
    for (auto & i : ownedTiles_)
        if (i && i->isBorder())
        for (auto & z : i->bordering_)
            if (z && z->owner_ != this) borderingStates_.insert(z->owner_);
}

void  Country::setOwnership(Country * owner, Pixel * ownee){
    owner->ownedTiles_.insert(ownee);
    ownee->owner_ = owner;
    ownee->rgba_ = owner->rgba_;
    owner->updateBorders();
}

bool Country::atWar(Country const * const a, Country const * const b){
    if (not a || not b) return true;
    bool res = a->warringStates_.contains(b);
    if (res != b->warringStates_.contains(a)) throw std::runtime_error(
        std::format("Inconsistent war state between {} and {} detected...\n", printColoredName(*a), printColoredName(*b)));
    return res;
}

void  Country::makeWar(Country* c, Country * p)
{
    if (not c || not p || c->atWar(p)) return;
    std::cout << "Diplomatic relations between " <<  printColoredName(*c) << " and " << printColoredName(*p) << " have broken down... war has been declared!\n";
    c->warringStates_.insert(p);
    c->atWar_ = true;
    p->warringStates_.insert(c);
    p->atWar_ = true;
}

void  Country::makePeace(Country* c, Country * p)
{
    if (not c || not p || not c->atWar(p)) return;
    std::cout << "Diplomatic relations between " <<  printColoredName(*c) << " and " << printColoredName(*p) << " have mended... peace in our time!\n";
    c->warringStates_.erase(p);
    c->atWar_ = false;
    p->warringStates_.erase(c);
    p->atWar_ = false;
}

constexpr std::tuple<uint8_t, uint8_t, uint8_t> Country::unpack_rgb(uint32_t rgba) {
    return {
        static_cast<uint8_t>((rgba >> 24) & 0xFF),
        static_cast<uint8_t>((rgba >> 16) & 0xFF),
        static_cast<uint8_t>((rgba >> 8) & 0xFF)
    };
}

// Returns a stream manipulator that sets the terminal color
std::string Country::printColoredName(const Country& c) {
    auto [r, g, b] = unpack_rgb(c.rgba_);
    std::stringstream ss;
    ss << "\033[48;2;"  << int(r) << ";" << int(g) << ";" << int(b) << "m" << c.name_ << "\033[0m";
    return ss.str();
}




