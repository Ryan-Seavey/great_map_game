//
// Created by diogenes on 4/28/25.
//

#ifndef TRADE_DEAL_HPP
#define TRADE_DEAL_HPP
#include <stdexcept>

struct Country;

struct Country_pair
{
    Country * a_, *b_;
    Country_pair(Country * a, Country * b)
    {
        if (a > b) std::swap(a,b);
        if (a == b) throw std::runtime_error("A country pair should not contain itself.");
        if (a == nullptr || b == nullptr) throw std::runtime_error("A country pair may not hold nullptr countries");
        a_ = a, b_ = b;
    }

    struct country_pair_hash
    {
        size_t operator()(const Country_pair& cp)  const noexcept {
            size_t h1 = std::hash<Country*>{}(cp.a_);
            size_t h2 = std::hash<Country*>{}(cp.b_);
            return h1^h2;
        }
    };
};

struct Trade_deal
{
    //IN NO PARTICULAR ORDER
    Country * partner_a, * partner_b;
    float quantity_a, quantity_b;
    float quality_a, quality_b;
    //TODO: make different goods for trade

};

#endif //TRADE_DEAL_HPP
