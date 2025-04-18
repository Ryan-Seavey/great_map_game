//
// Created by diogenes on 4/17/25.
//

#ifndef GOVERNMENT_H
#define GOVERNMENT_H
#include <string>

struct Government
{
    std::string name_{"The First Republic"};
    std::string ideology_{"Radical Centrism"};

    float authoritarianism_percent_ = 50;
    float liberalism_percent_ = 50;

    float corruption_percent_ = 0;

    float stability_percent_ = 50;
    float public_confidence_percent_ = 50;

    float bureaucratic_bloat_percent_;
};

#endif //GOVERNMENT_H
