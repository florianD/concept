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
            static const int MAP_WIDTH = 25;
            static const int MAP_HEIGHT = 1;
            static const int WILD_TILES = MAP_WIDTH * MAP_HEIGHT;
            static const int WILD_TILE_SPRITES = 12;
            static const int TILE_SIDE = 32;
            static const int LEVEL_WIDTH = 800 * TILE_SIDE/16;
            static const int LEVEL_HEIGHT = 800 * TILE_SIDE/16;
            Image d_tileWild;
            std::vector<SDL_Rect> d_tileClips;
            Tile *d_tileSet[WILD_TILES];
    };
}

#endif // MAP_H
