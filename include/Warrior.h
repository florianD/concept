#ifndef WARRIOR_H
#define WARRIOR_H
#include "Player.h"

namespace rpg
{
    class Warrior : public Player
    {
        public:
            Warrior(int x, int y, int vel, int vx, int vy, std::string name, int orientation);
            virtual double frameFromOri(double offset);
            virtual void walk();
            static bool loadSpriteSheet(SDL_Renderer *renderer);
            virtual void render(SDL_Renderer *renderer, SDL_Rect &cam);
            virtual ~Warrior();
        private:
            virtual void resetAnimation();
            static SDL_Rect d_spriteClips[144];
            static Image d_spriteSheetTexture;
    };
}

#endif // WARRIOR_H
