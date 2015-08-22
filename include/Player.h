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
            Player(int x, int y, int vel, int vx, int vy, std::string name, int orientation, SDL_Renderer *renderer);
            virtual bool loadSpriteSheet(SDL_Renderer *renderer);
            virtual void handleEvent(SDL_Event &e);
            virtual ~Player();
    };
}

#endif // PLAYER_H
