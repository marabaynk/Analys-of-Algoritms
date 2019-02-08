#include "cleaner.h"

Cleaner::Cleaner(double speed, std::mutex *m3)
{
    this->speed = speed;
    this->m3 = m3;
}

void Cleaner::run()
{
    while(true)
    {
        if (!clQue.empty())
        {
            m3->lock();
            activePlane = clQue.front();
            clQue.pop();
            m3->unlock();

            log.push_back(LogString(tClock.time(), activePlane.id, logStartMsg, "Cleaner"));
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
            activePlane.readiness = 100;
            log.push_back(LogString(tClock.time(), activePlane.id, logEndMsg, "Cleaner"));
            log.push_back(LogString(tClock.time(), activePlane.id, logLeaveMsg, "Cleaner"));            

            toSeat.push(activePlane);
            log.push_back(LogString(tClock.time(), activePlane.id, logFinalMsg, "Cleaner"));
        }
    }
}

std::list<LogString> Cleaner::getLog()
{
    return log;
}

