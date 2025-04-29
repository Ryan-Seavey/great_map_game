//
// Created by diogenes on 4/17/25.
//

#ifndef ECONOMY_H
#define ECONOMY_H
#include <unordered_map>
#include <unordered_set>
#include "Trade_deal.hpp"
struct Country;

struct Economy{
    //statics
    static inline std::unordered_map<Country_pair, Trade_deal, Country_pair::country_pair_hash> list_of_trade_deals;

    //mutables
    float civilian_taxRate_ = 50.f;
    float corporate_tax_rate_ = 50.f;
    float consumer_percent_;
    float service_percent_;
    float materiel_percent_;
    float black_market_percent_;
    float government_spending_;
    float cash_;
    float interest_rate_;
    std::unordered_set<struct Country *, float> list_of_tariff_percents_;

    //results
    float unemployment_;
    float inflation_;
    float GDP_;
    float willingness_to_invest_;
    float poverty_rate_;
    unsigned number_of_billionaires_;
    float value_of_currency = 1.f;
    float population_;

    enum Type {
        traditional,
        command,
        centrally_planned,
        mixed,
        market,
        laissez_faire,
    } type_;

    Economy();

    void printMoney(float);
    void changeIntrestRate(float);
    void subsidizeCivilianIndustry(float);
    void subsidizeMilitaryIndustry(float);
    void crackDownOnBlackMarket(float);
    void makeBackroomDeals(float);
    void modifyCivilianTaxes(float);
    void modifyCorporateTaxes(float);
    void bustTrusts(float);
    void relaxMonopolyLaws(float);
    void changeWelfareSpending(float);
    void nationalizeIndustry();
    void privatizeIndustry();
};

#endif //ECONOMY_H
