//
// Created by diogenes on 4/21/25.
//

#ifndef AI_CLEVER_HPP
#define AI_CLEVER_HPP
#include <unordered_set>

#include "../AI_Contract.hpp"


class AI_clever : public AI_module{
    //How much money this AI wants
    const unsigned char greediness_;
    //How much land this AI wants
    const unsigned char jingoism_;
    //How much this AI communicates with the others
    const unsigned char sociability_;
    //How likely this AI is to help its allies
    const unsigned char altruism_;

    //from -200 to 200?
    std::unordered_set<Country *, short> opinion_;

    const unsigned diplo_delay_days_;
    unsigned last_diplo_action_tick{};
public:
    AI_clever();
    void performDiplomacy(Country&) override;
    void manageEconomy(Country&) override;
    void attemptExpansion(Country&) override;
};



#endif //AI_CLEVER_HPP
