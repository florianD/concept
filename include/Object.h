#ifndef OBJECT_H
#define OBJECT_H
#include <SDL2/SDL.h>
#include <iostream>
#include "config.h"
using std::string;
using std::ostream;
using std::istream;
using std::endl;

namespace rpg
{
    class Object
    {
        public:
            virtual ~Object();
            virtual int getX() const = 0;
            virtual int getY() const = 0;
            virtual string getName() const = 0;
            virtual void setCamera(SDL_Rect &camera);
            virtual void render(SDL_Renderer *renderer, SDL_Rect &cam) = 0;
            virtual void renderT(SDL_Renderer *renderer, SDL_Rect &cam) = 0;
    };
}

#endif // OBJECT_H
