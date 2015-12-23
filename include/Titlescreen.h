#ifndef TITLESCREEN_H
#define TITLESCREEN_H
#include <sstream>
#include <SDL2/SDL_ttf.h>
#include "config.h"
#include "Logo.h"

namespace rpg
{
    class Titlescreen
    {
        public:
            Titlescreen(SDL_Renderer *renderer, TTF_Font *font);
            static bool loadImage(SDL_Renderer *renderer);
            void render(SDL_Renderer *renderer, Logo *logo);
            void setActive();
            bool getActive() const;
            ~Titlescreen();
        private:
            static Image d_image;
            bool d_isActive;
            static Image d_textureText;
    };
}

#endif // TITLESCREEN_H
