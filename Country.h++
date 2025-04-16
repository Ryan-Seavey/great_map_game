//
// Created by diogenes on 4/16/25.
//

#ifndef COUNTRY_H
#define COUNTRY_H
#include <string>
#include <unordered_set>
#include <utility>
#include "Pixel.h+="



struct Country {
    std::string name_{"Doesntexististan"};
    unsigned rgba_;
    std::unordered_set<Pixel*> ownedTiles_;


    Country() = default;
    Country(std::string name, unsigned color) : name_{std::move(name)}, rgba_{color}{};
    void setOwnership(Pixel * ownee);

    void tryExpand() {

    }
};

inline void setOwnership(Country * owner, Pixel * ownee){
    owner->ownedTiles_.insert(ownee);
    ownee->owner = owner;
    ownee->rgba_ = owner->rgba_;
}

inline void Country::setOwnership(Pixel* ownee){
    ::setOwnership(this, ownee);
}


#endif //COUNTRY_H
