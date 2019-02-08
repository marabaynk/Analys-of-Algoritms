#include <QCoreApplication>
#include <iostream>
#include <queue>
#include <mutex>
#include <QtConcurrent/qtconcurrentrun.h>
#include "cleaner.h"
#include "repairer.h"
#include "refueler.h"
#include "timeclock.h"

std::list<LogString> globallog;
std::queue<plane> repQue, refQue, clQue, toSeat;
class timeClock tClock;


void dispatch(uint speed, uint totalPlanes, std::mutex *m)
{
    uint countPlanes = 0;
    while (countPlanes < totalPlanes)
    {
        plane p(countPlanes, "Aeroflot", 0);
        globallog.push_back(LogString(tClock.time(), countPlanes++, "Added new plane", "Dispatcher"));
        m->lock();
        repQue.push(p);
        m->unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);    
    std::mutex m_repQue, m_refQue, m_clQue;
    Repairer rep(300, &m_repQue, &m_refQue);
    Refueler ref(600, &m_refQue, &m_clQue);
    Cleaner cl(200, &m_clQue);
    uint total = 5;

    std::thread th1(&Repairer::run, &rep);
    std::thread th2(&Refueler::run, &ref);
    std::thread th3(&Cleaner::run, &cl);

    dispatch(100, total, &m_repQue);

    while(toSeat.size() != total) {}

    th1.detach();
    th2.detach();
    th3.detach();

    std::list<LogString> replog = rep.getLog();
    std::list<LogString> reflog = ref.getLog();
    std::list<LogString> cllog = cl.getLog();

    globallog.splice(globallog.end(), replog);
    globallog.splice(globallog.end(), reflog);
    globallog.splice(globallog.end(), cllog);
    globallog.sort([](const LogString a, const LogString b)->bool
                        {
                            if ((int)(a.time - b.time) < 0)
                                return true;
                            else
                                return false; });
    for (LogString str : globallog)
        str.show();

    return 0;
}
