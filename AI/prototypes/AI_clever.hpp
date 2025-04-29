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

#define CINT static constexpr short
    //Bonus and maluses for diplomacy
    CINT MALUS_FIRST_MEET{-10};
    CINT BONUS_TRADE_DEAL{+35};
    CINT BONUS_MADE_TREATY{+75};
    CINT BONUS_MUTUAL_ENEMIES{+25};
    CINT MALUS_EXITED_ALLIANCE{-75};
    CINT MALUS_TREACHERY{-150};
    CINT MALUS_AT_WAR{-100};
    CINT BONUS_SAME_IDEOLOGY{+20};
#undef CINT
#define CUCH static constexpr unsigned char
    //thresholds for diplo 0-255
    CUCH DIPLO_WAR_WANT{200};
    CUCH DIPLO_PEACE_WANT{150};
    CUCH DIPLO_TRADE_WANT{150};
#undef CUCH
};



#endif //AI_CLEVER_HPP
