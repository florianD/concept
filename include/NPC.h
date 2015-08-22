#ifndef TRAINER_H
#define TRAINER_H
#include "Character.h"

namespace rpg
{
    class NPC : public Character
    {
        public:
            NPC(int x, int y, int vel, int vx, int vy, std::string name, int orientation, SDL_Renderer *renderer);
            virtual bool loadSpriteSheet(SDL_Renderer *renderer);
            virtual ~NPC();
    };
}

#endif // TRAINER_H
