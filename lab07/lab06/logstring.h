#ifndef LOGSTRING_H
#define LOGSTRING_H

#include <string>
#include <iostream>
#include <iomanip>

typedef struct LogString LogString;
struct LogString
{
    uint time = 0;
    uint id = 0;
    std::string action = "";
    std::string worker = "";

    LogString() {}
    LogString(uint t, uint i, std::string a, std::string w) :
        time(t), id(i), action(a), worker(w) {}

    void show()
    {
        std::setfill('0');
        std::left(std::cout);
        std::cout << std::setfill(' ') << std::setw(15) << "time : " + std::to_string(time);
        std::cout << " | ";
        std::cout << std::setfill(' ') << std::setw(10) << "plane : " + std::to_string(id);
        std::cout << " | ";
        std::cout << std::setfill(' ') << std::setw(45) << "action : " + action;
        std::cout << " | ";
        std::cout << std::setfill(' ') << std::setw(18) << "who : " + worker;
        std::cout << " | ";
        std::cout << std::endl;
    }
};

#endif // LOGSTRING_H
