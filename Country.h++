//
// Created by diogenes on 4/16/25.
//

#ifndef COUNTRY_H
#define COUNTRY_H
#include <string>
#include <unordered_set>
#include <utility>

#include "AI/AI_Contract.hpp"
#include "Pixel.h++"
#include "AI/AI_Contract.hpp"
#include "AI/prototypes/AI_dumb.hpp"
#include "AI/prototypes/AI_peaceful.h++"
#include "facets/Economy.h++"
#include "facets/Government.h++"
#include "facets/Military.h++"


struct Country {
    friend struct AI_module;
    std::string name_{"Doesntexististan"};
    unsigned rgba_;
    std::unordered_set<Pixel*> ownedTiles_;

    AI_module * brain = new AI_dumb;

    Military military_;
    Government gov_;
    Economy economy_;

    Country() = default;
    Country(std::string name, unsigned color);
    Country(std::string name, unsigned color, AI_module * ai);
    Country(unsigned color);
    ~Country();
    void setOwnership(Pixel * ownee);
    void update();
    size_t size() const {return ownedTiles_.size();}
};

void setOwnership(Country * owner, Pixel * ownee);

#endif //COUNTRY_H
