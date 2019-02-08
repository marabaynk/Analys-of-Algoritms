#ifndef CLEANER_H
#define CLEANER_H

#include <list>
#include <string>
#include <mutex>
#include <thread>
#include <queue>

#include "plane.h"
#include "logstring.h"
#include "timeclock.h"

extern std::queue<plane> clQue;
extern std::queue<plane> toSeat;
extern class timeClock tClock;

class Cleaner
{
public:
    Cleaner() {}
    explicit Cleaner(double speed, std::mutex *m3);
    ~Cleaner() {}
    void run();
    std::list<LogString> getLog();
private:    
    std::list<LogString> log;
    std::string logStartMsg = "Arrived at the plane wash";
    std::string logEndMsg = "Washed";
    std::string logLeaveMsg = "Departed from plane wash";
    std::string logFinalMsg = "Directed to seat";
    plane activePlane;
    uint speed = 500;
    std::mutex *m3 = nullptr;
};

#endif // CLEANER_H
