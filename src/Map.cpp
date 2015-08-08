#include "../include/Map.h"

namespace rpg
{
    Map::Map(SDL_Renderer *renderer)
    {
        d_tileClips.clear();

        //The tile offsets
        int x = 0, y = 0;

        //Determines what kind of tile will be made
        int tileType = -1;

        //Open the map
        std::ifstream map("world.map");

        //If the map couldn't be loaded
        if(map == NULL)
        {
            printf("Unable to load map file\n");
        }
        else
        {
            //Initialize the tiles
            for(int i = 0; i < WILD_TILES; ++i)
            {
                //Read tile from map file
                map >> tileType;

                //If the was a problem in reading the map
                if(map.fail())
                {
                    //Stop loading map
                    printf("Error loading map: Unexpected end of file\n");
                    break;
                }

                //If the number is a valid tile number
                if((tileType >= 0) && (tileType < WILD_TILE_SPRITES))
                {
                    d_tileSet[i] = new Tile(x, y, tileType);
                }
                //If we don't recognize the tile type
                else
                {
                    //Stop loading map
                    printf("Error loading map: Invalid tile type at %d\n", i);
                    break;
                }

                //Move to next tile spot
                x += TILE_SIDE;

                //If we've gone too far
                if(x >= LEVEL_WIDTH)
                {
                    //Move back
                    x = 0;

                    //Move to the next row
                    y += TILE_SIDE;
                }
            }
            loadSpriteSheetWild(renderer);
        }

        //Close the file
        map.close();
    }

    Map::~Map()
    {
        for(int i = 0; i < WILD_TILES; ++i)
        {
            delete d_tileSet[i];
        }
        delete[] d_tileSet;
        d_tileWild.free();
    }

    bool Map::loadSpriteSheetWild(SDL_Renderer *renderer)
    {
        bool success = true;

        if(!d_tileWild.load("img/map/wild.png", renderer))
        {
            printf("Failed to load wild texture\n");
            success = false;
        }
        else
        {
            d_tileClips.reserve(WILD_TILE_SPRITES);

            int k = 0;
            for(int i = 0; i < 3; ++i)
            {
                for(int j = 0; j < 4; ++j)
                {
                    d_tileClips[k].x = j * TILE_SIDE;
                    d_tileClips[k].y = i * TILE_SIDE;
                    d_tileClips[k].w = TILE_SIDE;
                    d_tileClips[k++].h = TILE_SIDE;
                }
            }
        }
        return success;
    }
}
