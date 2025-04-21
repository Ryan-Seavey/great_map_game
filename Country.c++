//
// Created by diogenes on 4/21/25.
//
#include "Country.h++"

Country::Country(std::string name, unsigned color): name_{std::move(name)}, rgba_{color}
{}

Country::Country(std::string name, unsigned color, AI_module* ai): name_{std::move(name)}, rgba_{color}, brain{ai}
{}

Country::Country(unsigned color): rgba_{color}
{}


void Country::setOwnership(Pixel* ownee){
    ::setOwnership(this, ownee);
}

void Country::update() {
    brain->attemptExpansion(*this);
    brain->manageEconomy(*this);
    brain->performDiplomacy(*this);
}

Country::~Country(){
    delete brain;
    if (ownedTiles_.empty()) return;
    for (auto & i : ownedTiles_)
    {
        i->owner_ = nullptr;
    }
}

void setOwnership(Country * owner, Pixel * ownee){
    owner->ownedTiles_.insert(ownee);
    ownee->owner_ = owner;
    ownee->rgba_ = owner->rgba_;
}