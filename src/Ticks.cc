#include "Ticks.hh"
Tick secondsToTicks(float s)
{
    return (Tick)(s * TICKS_PER_SECOND);
}
float ticksToSeconds(Tick t)
{
    return (float)t / TICKS_PER_SECOND;
}

