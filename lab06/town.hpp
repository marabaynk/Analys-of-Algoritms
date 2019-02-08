#ifndef TOWN_HPP
#define TOWN_HPP

#include "ant.hpp"

class Town
{
public:
    Town();
    Town(int id);
    ~Town();

    void showTown();

    void addAnt(const Ant& ant);
    int getAntCount();

private:
    int townID;
    int antCount;
    std::vector<Ant> ants;
};

#endif // TOWN_HPP