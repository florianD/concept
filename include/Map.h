#ifndef MAP_H
#define MAP_H
#include <fstream>
#include "Image.h"
#include "Tile.h"

namespace rpg
{
    class Map
    {
        public:
            Map(SDL_Renderer *renderer);
            ~Map();
            bool loadSpriteSheetWild(SDL_Renderer *renderer);
            static const int MAP_WIDTH = config::MAP_WIDTH;
            static const int MAP_HEIGHT = config::MAP_HEIGHT;
            static const int WILD_TILES = MAP_WIDTH * MAP_HEIGHT;
            static const int TILE_SIDE_X = config::SIDE_X;
            static const int TILE_SIDE_Y = config::SIDE_Y;
            static const int LEVEL_WIDTH = config::LEVEL_W;
            static const int LEVEL_HEIGHT = config::LEVEL_H;
            static const int WILD_TILE_SPRITES = 12;
            Image d_tileWild;
            std::vector<SDL_Rect> d_tileClips;
            std::vector<std::vector<Tile*> > d_tileSet;
    };
}

#endif // MAP_H
