#ifndef SORCERER_H
#define SORCERER_H
#include "Player.h"

namespace rpg
{
    class Sorcerer : public Player
    {
        public:
            Sorcerer(int x, int y, int vel, int vx, int vy, std::string name, int orientation);
            virtual double frameFromOri(double offset);
            virtual void walk();
            static bool loadSpriteSheet(SDL_Renderer *renderer);
            virtual void render(SDL_Renderer *renderer, SDL_Rect &cam);
            virtual ~Sorcerer();
        private:
            virtual void resetAnimation();
            static SDL_Rect d_spriteClips[128];
            static Image d_spriteSheetTexture;
    };
}

#endif // SORCERER_H
