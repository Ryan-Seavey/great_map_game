//
// Created by diogenes on 4/17/25.
//

#ifndef AI_PEACEFUL_H
#define AI_PEACEFUL_H
#include "../AI_Contract.hpp"


class AI_peaceful : public AI_module {
public:
    ~AI_peaceful() override = default;
    void performDiplomacy(Country&) override{};
    void manageEconomy(Country&) override{};
    void attemptExpansion(Country&) override;
};



#endif //AI_PEACEFUL_H
