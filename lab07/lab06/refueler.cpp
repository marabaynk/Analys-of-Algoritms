#include "refueler.h"

Refueler::Refueler(double speed, std::mutex *m2, std::mutex *m3)
{
    this->speed = speed;
    this->m2 = m2;
    this->m3 = m3;
}

void Refueler::run()
{
    while(true)
    {
        if (!refQue.empty())
        {
            m2->lock();
            activePlane = refQue.front();
            refQue.pop();
            m2->unlock();

            log.push_back(LogString(tClock.time(), activePlane.id, logStartMsg, "Refueler"));
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
            activePlane.readiness = 0.66;
            log.push_back(LogString(tClock.time(), activePlane.id, logEndMsg, "Refueler"));
            log.push_back(LogString(tClock.time(), activePlane.id, logLeaveMsg, "Refueler"));            

            m3->lock();
            clQue.push(activePlane); // МЬЮТЕКСЫ
            m3->unlock();
        }
    }
}

std::list<LogString> Refueler::getLog()
{
    return log;
}
