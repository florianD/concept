#ifndef TIMER_H
#define TIMER_H
#include <SDL2/SDL.h>

namespace rpg
{
    class Timer
    {
        public:
            Timer();
            ~Timer();
            void start();
            void stop();
            void pause();
            void unpause();
            Uint32 getTicks() const;
            bool isStarted() const;
            bool isPaused() const;
        private:
            Uint32 d_startTicks;
            Uint32 d_pausedTicks;
            bool d_paused;
            bool d_started;
    };
}

#endif // TIMER_H
