#ifndef TRAINER_H
#define TRAINER_H
#include "Character.h"

namespace rpg
{
    class NPC : public Character
    {
        public:
            NPC(int x, int y, int vel, int vx, int vy, std::string name, int orientation, SDL_Renderer *renderer);
            static bool loadSpriteSheet(SDL_Renderer *renderer);
            virtual void render(SDL_Renderer *renderer, SDL_Rect &cam);
            virtual ~NPC();
        private:
            static SDL_Rect d_spriteClips[128];
            static Image d_spriteSheetTexture;
    };
}

#endif // TRAINER_H
