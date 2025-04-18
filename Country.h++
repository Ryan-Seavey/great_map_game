//
// Created by diogenes on 4/16/25.
//

#ifndef COUNTRY_H
#define COUNTRY_H
#include <string>
#include <unordered_set>
#include <utility>

#include "AI/AI_Contract.hpp"
#include "Pixel.h++"
#include "AI/AI_Contract.hpp"
#include "AI/prototypes/AI_dumb.hpp"
#include "AI/prototypes/AI_peaceful.h++"


struct Country {
    friend struct AI_module;
    std::string name_{"Doesntexististan"};
    unsigned rgba_;
    std::unordered_set<Pixel*> ownedTiles_;

    AI_module * brain = new AI_dumb;

    Country() = default;
    Country(std::string name, unsigned color) : name_{std::move(name)}, rgba_{color}{};
    ~Country();
    void setOwnership(Pixel * ownee);
    void update();
    size_t size() const {return ownedTiles_.size();}
};

inline void setOwnership(Country * owner, Pixel * ownee){
    owner->ownedTiles_.insert(ownee);
    ownee->owner_ = owner;
    ownee->rgba_ = owner->rgba_;
}

inline void Country::setOwnership(Pixel* ownee){
    ::setOwnership(this, ownee);
}

inline void Country::update() {
    brain->attemptExpansion(*this);
    brain->manageEconomy(*this);
    brain->performDiplomacy(*this);
}

inline Country::~Country(){
    if (ownedTiles_.empty()) return;
    for (auto & i : ownedTiles_)
    {
        i->owner_ = nullptr;
    }
    delete brain;
}


#endif //COUNTRY_H
