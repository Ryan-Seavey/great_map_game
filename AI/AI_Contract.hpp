//
// Created by diogenes on 4/17/25.
//

#ifndef AI_CONTRACT_HPP
#define AI_CONTRACT_HPP

struct Country;

struct AI_module
{
    virtual ~AI_module() = default;

    virtual void performDiplomacy(Country&) = 0;
    virtual void manageEconomy(Country&) = 0;
    virtual void attemptExpansion(Country&) = 0;

    enum class WarState {
        at_peace,
        attacking_winning,
        defending_winning,
        attacking_losing,
        defending_losing,
        stalemate,
        panicking
    } war_state_{WarState::at_peace};
    enum class EconomicState {
        stagflation = -2,
        recession = -1,
        stagnation,
        expansion,
    } economic_state_{EconomicState::stagnation};

};

#endif //AI_CONTRACT_HPP
