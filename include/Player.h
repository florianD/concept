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
            static bool loadSpriteSheet(SDL_Renderer *renderer);
            virtual void render(SDL_Renderer *renderer, SDL_Rect &cam);
            virtual void handleEvent(SDL_Event &e);
            virtual ~Player();
        private:
            static SDL_Rect d_spriteClips[128];
            static Image d_spriteSheetTexture;
    };
}

#endif // PLAYER_H
