#ifndef TIMECLOCK_H
#define TIMECLOCK_H

#include <chrono>

class timeClock
{
public:
    timeClock()
    {
        this->startPoint = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
    }
    ~timeClock() {}

    unsigned int time()
    {
        std::chrono::microseconds currPoint =
                std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch());
        return (currPoint - startPoint).count();
    }
private:
    std::chrono::microseconds startPoint;
};

#endif // TIMECLOCK_H
