#ifndef REPAIRER_H
#define REPAIRER_H

#include <list>
#include <string>
#include <thread>
#include <mutex>
#include <queue>

#include "plane.h"
#include "logstring.h"
#include "timeclock.h"

extern std::queue<plane> repQue;
extern std::queue<plane> refQue;
extern class timeClock tClock;


class Repairer
{
public:
    Repairer() {}
    explicit Repairer(double speed, std::mutex *m1, std::mutex *m2);
    ~Repairer() {}
    void run();
    std::list<LogString> getLog();
private:
    std::list<LogString> log;
    std::string logStartMsg = "Arrived at the service station";
    std::string logEndMsg = "Maintenance successfully completed";
    std::string logLeaveMsg = "Departed from service station";
    plane activePlane;
    uint speed = 500;
    std::mutex *m1 = nullptr, *m2 = nullptr;
};

#endif // REPAIRER_H
