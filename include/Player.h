#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include "Character.h"

namespace rpg
{
    class Player : public Character
    {
        public:
            Player(int x, int y, int vel, int vx, int vy, std::string name, int orientation);
            virtual void render(SDL_Renderer *renderer, SDL_Rect &cam) = 0;
            virtual void handleEvent(SDL_Event &e);
            virtual ~Player();
        protected:
            virtual void resetAnimation() = 0;
    };
}

#endif // PLAYER_H
