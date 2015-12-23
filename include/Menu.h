#ifndef MENU_H
#define MENU_H
#include <sstream>
#include <SDL2/SDL_ttf.h>
#include "config.h"
#include "Logo.h"
#include "Pentagram.h"

namespace rpg
{
    class Menu
    {
        public:
            Menu(SDL_Renderer *renderer);
            static bool loadImage(SDL_Renderer *renderer);
            void render(SDL_Renderer *renderer, Logo *logo, Pentagram *pentagram);
            void setActive();
            bool getActive() const;
            void setSelection(int sel);
            int getSelection() const;
            int getNbOptions() const;
            ~Menu();
        private:
            int i;
            static const int OPTIONS;
            static int d_pos[3];
            static Image d_image;
            bool d_isActive;
            static Image d_textureText[3];
            int d_x, d_y;
    };
}

#endif // MENU_H
