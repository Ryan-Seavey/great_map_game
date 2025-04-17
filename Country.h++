//
// Created by diogenes on 4/16/25.
//

#ifndef COUNTRY_H
#define COUNTRY_H
#include <string>
#include <unordered_set>
#include <utility>
#include "Pixel.h++"



struct Country {
    std::string name_{"Doesntexististan"};
    unsigned rgba_;
    std::unordered_set<Pixel*> ownedTiles_;


    Country() = default;
    Country(std::string name, unsigned color) : name_{std::move(name)}, rgba_{color}{};
    ~Country();
    void setOwnership(Pixel * ownee);

    void tryExpand();
    size_t size() const {return ownedTiles_.size();}
};

inline void setOwnership(Country * owner, Pixel * ownee){
    owner->ownedTiles_.insert(ownee);
    ownee->owner = owner;
    ownee->rgba_ = owner->rgba_;
}

inline void Country::setOwnership(Pixel* ownee){
    ::setOwnership(this, ownee);
}

inline void Country::tryExpand() {
    std::unordered_set<Pixel*> newClaims;

    for (Pixel* p : ownedTiles_) {
        for (Pixel* neighbor : p->bordering) {
            if (neighbor && neighbor->owner != this) {
                if (RyUtil::randint(0,1) & 1)
                newClaims.insert(neighbor);
            }
        }
    }

    for (Pixel* p : newClaims) {
        if (p->owner) {
            // Remove from old owner's list
            p->owner->ownedTiles_.erase(p);
        }
        setOwnership(p);
    }
}

inline Country::~Country(){
    if (ownedTiles_.empty()) return;
    for (auto & i : ownedTiles_)
    {
        i->owner = nullptr;
    }
}


#endif //COUNTRY_H
