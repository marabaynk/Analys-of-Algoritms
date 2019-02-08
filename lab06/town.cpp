#include <iostream>

#include "town.hpp"
#include "ant.hpp"

Town::Town(){}
Town::Town(int id) : townID(id), antCount(0) {}
Town::~Town(){}

void Town::addAnt(const Ant& ant)
{
    ants.push_back(ant);
    antCount++;
}

int Town::getAntCount()
{
    return antCount;
}

void Town::showTown()
{
    std::cout << "Town ID: " << townID << std::endl;
    std::cout << "Ant Count: " << antCount << std::endl;
}