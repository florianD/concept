#ifndef OBJECT_H
#define OBJECT_H
#include <SDL2/SDL.h>
#include <iostream>
#include "config.h"

namespace rpg
{
    class Object
    {
        public:
            virtual ~Object();
            virtual int getX() const = 0;
            virtual int getY() const = 0;
            virtual std::string getName() const = 0;
            virtual void render(SDL_Renderer *renderer, SDL_Rect &cam) = 0;
    };
}

#endif // OBJECT_H
