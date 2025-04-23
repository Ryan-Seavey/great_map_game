//
// Created by diogenes on 4/17/25.
//
#include "AI_dumb.hpp"
#include "../../Country.h++"
#include "../../Pixel.h++"
#include "../../RyUtil.h++"

void AI_dumb::attemptExpansion(Country& c)
{
    std::unordered_set<Pixel*> newClaims;

    for (Pixel* p : c.ownedTiles_) {
        for (Pixel* neighbor : p->bordering_) {
            if (neighbor && neighbor->owner_ != &c) {
                if (RyUtil::randint(0,1) & 1)
                    newClaims.insert(neighbor);
            }
        }
    }

    for (Pixel* p : newClaims) {
        if (p->owner_) {
            // Remove from old owner_'s list
            p->owner_->ownedTiles_.erase(p);
        }
        Country::setOwnership(&c, p);
    }
}