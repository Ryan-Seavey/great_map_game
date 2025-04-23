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

void AI_clever::attemptExpansion(Country&)
{
}
