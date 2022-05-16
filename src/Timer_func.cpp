#include "Timer.hpp"
Timer::Timer(){
    startTime = 0;
}
void Timer::updateTime(){
    startTime = SDL_GetTicks();
}
Uint32 Timer::distanceTime(){
    return SDL_GetTicks() - startTime;
}
