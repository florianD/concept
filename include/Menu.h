#ifndef MENU_H
#define MENU_H
#include <SDL2/SDL.h>
#include "Image.h"

namespace rpg
{
    class Menu
    {
        public:
            Menu(SDL_Renderer *renderer);
            static bool loadSpriteSheet(SDL_Renderer *renderer);
            void animate();
            void render(SDL_Renderer *renderer);
            ~Menu();
        private:
            static SDL_Rect d_spriteClips[15];
            static Image d_spriteSheetTexture;
            double d_frame, d_offset;
            int d_clip;
    };
}

#endif // MENU_H
