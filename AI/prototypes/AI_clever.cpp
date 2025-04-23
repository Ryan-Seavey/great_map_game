//
// Created by diogenes on 4/21/25.
//

#include "AI_clever.hpp"

#include "../../Country.h++"
#include "../../RyUtil.h++"

AI_clever::AI_clever() :
greediness_{RyUtil::random(0.f, 100.f)},
jingoism_{RyUtil::random(0.f, 100.f)},
sociability_{RyUtil::random(0.f, 100.f)},
altruism_{RyUtil::random(0.f, 100.f)}
{

}

void AI_clever::performDiplomacy(Country&)
{

}

void AI_clever::manageEconomy(Country& c)
{
   // if (c.economy_.delta_gdp < 0)
}

void AI_clever::attemptExpansion(Country& c)
{
   std::unordered_set<Pixel*> newClaims;

   for (Pixel* p : c.ownedTiles_) { //TODO: only search through border tiles.
      if (not p->isBorder()) continue;;
      for (Pixel* neighbor : p->bordering_) {
         if (not neighbor || neighbor->owner_ == &c || not c.atWar(neighbor->owner_)) continue;
         if (RyUtil::randint(0,1) & 1) //TODO: combat mechanic
            newClaims.insert(neighbor);
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
