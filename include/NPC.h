#ifndef TRAINER_H
#define TRAINER_H
#include "Character.h"

namespace rpg
{
    class NPC : public Character
    {
        public:
            NPC(int x, int y, int vel, int vx, int vy, string name, int orientation, SDL_Renderer *renderer);
            virtual bool loadSpriteSheet(SDL_Renderer *renderer);
            virtual ~NPC();
        private:
    };
}

#endif // TRAINER_H
