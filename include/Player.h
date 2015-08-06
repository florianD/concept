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
            Player(int x, int y, int vel, int vx, int vy, string name, int orientation, SDL_Renderer *renderer);
            virtual void renderT(SDL_Renderer *renderer, SDL_Rect &cam);
            virtual bool loadSpriteSheet(SDL_Renderer *renderer);
            virtual void handleEvent(SDL_Event &e);
            virtual ~Player();
        private:
    };
}

#endif // PLAYER_H
