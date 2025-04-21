//
// Created by diogenes on 4/17/25.
//

#ifndef ECONOMY_H
#define ECONOMY_H

struct Economy{
    //mutables
    float taxRate_ = 50.f;
    float consumer_percent_;
    float service_percent_;
    float materiel_percent_;
    float black_market_percent_;
    std::unordered_set<Country *, float> list_of_tariff_percents_;

    //results
    float unemployment = 4.0f;
    float inflation = 2.0f;
    float GDP = 100;
    unsigned number_of_billionaires_;

    enum Type {
        traditional,
        command,
        centrally_planned,
        mixed,
        market,
        laissez_faire,
    } type_;

};

#endif //ECONOMY_H
