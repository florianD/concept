#ifndef Logo_H
#define Logo_H
#include <SDL2/SDL.h>
#include "Image.h"

namespace rpg
{
    class Logo
    {
        public:
            Logo();
            static bool loadSpriteSheet(SDL_Renderer *renderer);
            void animate();
            void render(SDL_Renderer *renderer, int x, int y);
            ~Logo();
        private:
            static SDL_Rect d_spriteClips[15];
            static Image d_spriteSheetTexture;
            double d_frame, d_offset;
            int d_clip;
    };
}

#endif // MENU_H

