#ifndef TILE_H
#define TILE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "config.h"
#include "Image.h"

namespace rpg
{
    class Tile
    {
        public:
            Tile(int x, int y, int type);
            void render(Image &im, SDL_Renderer *renderer, SDL_Rect &camera, std::vector<SDL_Rect> &tileClips);
            int getType() const;
            SDL_Rect getBox() const;
            ~Tile();
        private:
            SDL_Rect d_box;
            int d_type;
    };
}

#endif // TILE_H
