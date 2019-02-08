#ifndef ANT_HPP
#define ANT_HPP

#include <vector>
#include "main.hpp"

class Ant
{
public:
    void updateRoad(int townID, int distance);
    std::vector<int>& getDestinations();
    std::vector<int>& getRoute();
    float getPheromon();
    int getRouteLenght();
    void showAnt();
    Ant();
    Ant(int townID);
    ~Ant();
private:
    std::vector<int> route;
    std::vector<int> routeDistances;
    std::vector<int> destinations;
    float pheromon = Q;
    int routeLength;
};

#endif // ANT_HPP