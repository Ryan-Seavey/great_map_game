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
#include "RyUtil.h++"
#include "facets/Economy.h++"
#include "facets/Government.h++"
#include "facets/Military.h++"


struct Country {
    friend struct AI_module;
    std::string name_{"Doesntexististan"};
    unsigned rgba_;
    bool atWar_{};
    std::unordered_set<Pixel*> ownedTiles_;
    std::unordered_set<Country const *> warringStates_;
    std::unordered_set<Country *> borderingStates_;

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
    [[nodsicard]] bool atWar(Country*) const;
    void makeWar(Country *);
    void makePeace(Country *);
    void updateBorders();

    static void setOwnership(Country * owner, Pixel * ownee);
    static bool atWar(Country const *, Country const *) exceptional;
    static void makeWar(Country *, Country *);
    static void makePeace(Country *, Country *);

    static constexpr std::tuple<uint8_t, uint8_t, uint8_t> unpack_rgb(uint32_t rgba);
    static std::string printColoredName(const Country& c);
};




#endif //COUNTRY_H
