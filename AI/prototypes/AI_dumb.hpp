//
// Created by diogenes on 4/17/25.
//

#ifndef AI_DUMB_HPP
#define AI_DUMB_HPP
#include "../AI_Contract.hpp"

class AI_dumb : public AI_module{
public:
    ~AI_dumb() override = default;
    void performDiplomacy(Country&){}
    void manageEconomy(Country&){}
    void attemptExpansion(Country&);
};

#endif //AI_DUMB_HPP
