//
// Created by diogenes on 4/21/25.
//

#include "AI_clever.hpp"

#include "../../Country.h++"
#include "../../RyUtil.h++"
#include "../../constants.c++"

AI_clever::AI_clever() :
greediness_{RyUtil::random<unsigned char>(0u, 255u)},
jingoism_{RyUtil::random<unsigned char>(0u, 255u)},
sociability_{RyUtil::random<unsigned char>(0u, 255u)},
altruism_{RyUtil::random<unsigned char>(0u, 255u)},
diplo_delay_days_(RyUtil::random(0.f, 24.f) * ticks::TICKS_PER_MONTH)
{

}

void AI_clever::performDiplomacy(Country& c)
{
   if (ticks::GLOBAL_TICK - last_diplo_action_tick < diplo_delay_days_)
      return;
   for (auto &i : c.borderingStates_)
   {
      unsigned char how_am_I_feeling = RyUtil::random(0, 255);
      bool how_goes_the_war = i->atWar(&c);
      if (how_goes_the_war && how_am_I_feeling + jingoism_ > DIPLO_WAR_WANT)
      {
         Country::makePeace(i, &c);
         last_diplo_action_tick = ticks::GLOBAL_TICK;
         return;
      }
      else if (not how_goes_the_war && how_am_I_feeling + sociability_ + altruism_ - jingoism_ > DIPLO_PEACE_WANT)
      {
         Country::makeWar(i, &c);
         last_diplo_action_tick = ticks::GLOBAL_TICK;
         return;
      } else if (not how_goes_the_war &&
         how_am_I_feeling + sociability_ + altruism_ + greediness_ + Economy::list_of_trade_deals.contains({&c, i}) * DIPLO_RENEGOTIATE_WANT > DIPLO_TRADE_WANT)
      {
         c.makeTrade(i);
         last_diplo_action_tick = ticks::GLOBAL_TICK;
         return;
      }
   }
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
