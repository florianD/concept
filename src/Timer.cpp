#include "../include/Timer.h"

namespace rpg
{
    Timer::Timer() : d_startTicks(0), d_pausedTicks(0), d_paused(false), d_started(false){}

    Timer::~Timer(){}

    void Timer::start()
    {
        d_started = true;
        d_paused = false;

        d_startTicks = SDL_GetTicks();
        d_pausedTicks = 0;
    }

    void Timer::stop()
    {
        d_started = false;
        d_paused = false;
        d_startTicks = 0;
        d_pausedTicks = 0;
    }

    void Timer::pause()
    {
        if(d_started && !d_paused)
        {
            d_paused = true;

            d_pausedTicks = SDL_GetTicks() - d_startTicks;
            d_startTicks = 0;
        }
    }

    void Timer::unpause()
    {
        if(d_started && d_paused)
        {
            d_paused = false;
            d_startTicks = SDL_GetTicks() - d_pausedTicks;

            d_pausedTicks = 0;
        }
    }

    Uint32 Timer::getTicks() const
    {
        Uint32 time = 0;

        if(d_started)
        {
            if(d_paused)
            {
                time = d_pausedTicks;
            }
            else
            {
                time = SDL_GetTicks() - d_startTicks;
            }
        }
        return time;
    }

    bool Timer::isStarted() const
    {
        return d_started;
    }

    bool Timer::isPaused() const
    {
        return d_paused && d_started;
    }
}
