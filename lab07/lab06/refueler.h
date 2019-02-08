#ifndef REFUELER_H
#define REFUELER_H

#include <list>
#include <string>
#include <mutex>
#include <thread>
#include <queue>

#include "logstring.h"
#include "plane.h"
#include "timeclock.h"

extern std::queue<plane> refQue;
extern std::queue<plane> clQue;
extern class timeClock tClock;

class Refueler
{
public:
    Refueler() {}
    explicit Refueler(double speed, std::mutex *m2, std::mutex *m3);
    ~Refueler() {}
    void run();
    std::list<LogString> getLog();
private:
    std::list<LogString> log;
    std::string logStartMsg = "Arrived at the fuel station";
    std::string logEndMsg = "Fueled";
    std::string logLeaveMsg = "Departed from fuel station";
    plane activePlane;
    uint speed = 500;
    std::mutex *m2 = nullptr, *m3 = nullptr;
};

#endif // REFUELER_H
