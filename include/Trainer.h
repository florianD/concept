#ifndef TRAINER_H
#define TRAINER_H
#include "Character.h"

namespace rpg
{
    class Trainer : public Character
    {
        public:
            Trainer(int x, int y, int vel, int vx, int vy, int id, string name, int orientation, SDL_Renderer *renderer);
            virtual bool loadSpriteSheet(SDL_Renderer *renderer);
            virtual ~Trainer();
        private:
    };
}

#endif // TRAINER_H
