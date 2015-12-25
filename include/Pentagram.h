#ifndef PENTAGRAM_H
#define PENTAGRAM_H
#include <SDL2/SDL.h>
#include "Image.h"

namespace rpg
{
    class Pentagram
    {
        public:
            Pentagram();
            static bool loadSpriteSheet(SDL_Renderer *renderer, std::string path);
            void animate();
            void render(SDL_Renderer *renderer, int x, int y);
            int getHeight() const;
            int getWidth() const;
            ~Pentagram();
        private:
            static SDL_Rect d_spriteClips[8];
            static Image d_spriteSheetTexture;
            double d_frame, d_offset;
            int d_clip;
    };
}

#endif // PENTAGRAM_H
