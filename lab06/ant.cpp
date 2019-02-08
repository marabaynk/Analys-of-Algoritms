#include <iostream>

#include "main.hpp"
#include "ant.hpp"

Ant::Ant(){}
Ant::Ant(int townID)
{
    for (int i = 0; i < TOWN_COUNT; i++)
    {
        if (i != townID)
        {
            destinations.push_back(i);
        }
    }

    route.push_back(townID);
    routeLength = 0;
}
Ant::~Ant(){}

int Ant::getRouteLenght(){
    return routeLength;
}

std::vector<int>& Ant::getDestinations()
{
    return destinations;
}

std::vector<int>& Ant::getRoute()
{
    return route;
}

void Ant::updateRoad(int townID, int distance)
{
    route.push_back(townID);
    routeDistances.push_back(distance);
    destinations.erase(std::remove(destinations.begin(), destinations.end(), townID), destinations.end());
    routeLength += distance;
}

void Ant::showAnt()
{
    std::cout << "Destinations: ";
    for (int i = 0; i < destinations.size(); i++)
    {
        std::cout << destinations[i] << (i < destinations.size() - 1 ? ", " : "\n");
    }

    std::cout << "Current length: " << routeLength << std::endl;

    std::cout << "Road: ";
    for (int i = 0; i < route.size(); ++i)
    {
        std::cout << route[i] << (i < route.size() - 1 ? " --> " : "\n");
    }

    std::cout << "Dist:    ";
    if (routeDistances.size() == 0)
    {
        std::cout << std::endl; // Add newline if distances' array is not defined
        return;
    }
    for (int i = 0; i < routeDistances.size(); ++i)
    {
        std::cout << routeDistances[i] << (i < routeDistances.size() - 1 ? " --- " : "\n");
    }
    std::cout << getPheromon() << std::endl;
}



float Ant::getPheromon()
{
    return pheromon / routeLength;
}


