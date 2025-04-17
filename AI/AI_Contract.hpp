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
};

#endif //AI_CONTRACT_HPP
