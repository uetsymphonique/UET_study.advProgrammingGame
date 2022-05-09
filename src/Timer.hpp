#ifndef TIMERCLASS__
#define TIMERCLASS__
#include "params.hpp"
class Timer
{
public:
    Timer();
    void updateTime();
    Uint32 distanceTime();
private:
    Uint32 startTime;
};

#endif // TIMERCLASS__
