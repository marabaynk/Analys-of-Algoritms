#include "repairer.h"

Repairer::Repairer(double speed, std::mutex *m1, std::mutex *m2)
{
    this->speed = speed;
    this->m1 = m1;
    this->m2 = m2;
}

void Repairer::run()
{
    while(true)
    {
        if (!repQue.empty())
        {           
            m1->lock();
            activePlane = repQue.front();
            repQue.pop();
            m1->unlock();

            log.push_back(LogString(tClock.time() , activePlane.id, logStartMsg, "Repairer"));
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
            activePlane.readiness = 0.33;
            log.push_back(LogString(tClock.time(), activePlane.id, logEndMsg, "Repairer"));
            log.push_back(LogString(tClock.time(), activePlane.id, logLeaveMsg, "Repairer"));            

            m2->lock();
            refQue.push(activePlane);
            m2->unlock();
        }
    }
}

std::list<LogString> Repairer::getLog()
{
    return log;
}
