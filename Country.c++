//
// Created by diogenes on 4/21/25.
//
#include "Country.h++"

#include <stdexcept>

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

void  Country::setOwnership(Country * owner, Pixel * ownee){
    owner->ownedTiles_.insert(ownee);
    ownee->owner_ = owner;
    ownee->rgba_ = owner->rgba_;
}

bool Country::atWar(Country const * const a, Country const * const b){
    bool res = a->warringStates_.contains(b);
    if (res != b->warringStates_.contains(a)) throw std::runtime_error("Inconsistent war state between countries detected...\n");
    return res;
}

void  Country::makeWar(Country* c, Country * p)
{
    c->warringStates_.insert(p);
    c->atWar_ = true;
    p->warringStates_.insert(c);
    p->atWar_ = true;
}

void  Country::makePeace(Country* c, Country * p)
{
    c->warringStates_.erase(p);
    c->atWar_ = false;
    p->warringStates_.erase(c);
    p->atWar_ = false;
}




