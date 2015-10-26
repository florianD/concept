#include "../include/Map.h"

namespace rpg
{
    Map::Map(SDL_Renderer *renderer)
    {
        d_tileClips.clear();
        d_tileSet.clear();

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
            d_tileSet.resize(MAP_HEIGHT);
            for(int i = 0; i < MAP_HEIGHT; ++i)
            {
                d_tileSet[i].resize(MAP_WIDTH);
            }

            //Initialize the tiles
            for(int i = 0; i < MAP_HEIGHT; ++i)
            {
                for(int j = 0; j < MAP_WIDTH; ++j)
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
                        d_tileSet[i][j] = new Tile(x, y, tileType);
                    }
                    //If we don't recognize the tile type
                    else
                    {
                        //Stop loading map
                        printf("Error loading map: Invalid tile type at %d\n", i);
                        break;
                    }

                    //Move to next tile spot
                    x += TILE_SIDE_X;

                    //If we've gone too far
                    if(x >= LEVEL_WIDTH)
                    {
                        //Move back
                        x = 0;

                        //Move to the next row
                        y += TILE_SIDE_Y;
                    }
                }
            }
            loadSpriteSheetWild(renderer);
        }

        //Close the file
        map.close();
    }

    Map::~Map()
    {
        for(int i = 0; i < MAP_HEIGHT; ++i)
        {
            for(int j = 0; j < MAP_WIDTH; ++j)
            {
                delete d_tileSet[i][j];
            }
            d_tileSet[i].clear();
        }
        d_tileWild.free();
    }

    bool Map::loadSpriteSheetWild(SDL_Renderer *renderer)
    {
        bool success = true;

        if(!d_tileWild.load("img/map/cathedral.png", renderer))
        {
            printf("Failed to load wild texture\n");
            success = false;
        }
        else
        {
            d_tileClips.resize(WILD_TILE_SPRITES);

            int k = 0;
            /*for(int i = 0; i < 1; ++i)
            {
                for(int j = 0; j < 6; ++j)
                {
                    d_tileClips[k].x = j * TILE_SIDE_X;
                    d_tileClips[k].y = i * TILE_SIDE_Y*3;
                    d_tileClips[k].w = TILE_SIDE_X;
                    d_tileClips[k++].h = TILE_SIDE_Y*3;
                }
            }*/

            int offset_h = 0;
            int offset_w = 0;

            for(int i = 0; i < 10; ++i)
            {
                for(int j = 0; j < 20; ++j)
                {
                    d_tileClips[k].x = j * TILE_SIDE_X + offset_w;
                    d_tileClips[k].y = i * TILE_SIDE_Y*3 + offset_h;
                    d_tileClips[k].w = TILE_SIDE_X;
                    d_tileClips[k++].h = TILE_SIDE_Y*3;
                    offset_w++;
                }
                offset_w = 0;
                offset_h++;
            }
            for(int i = 10; i < 11; ++i)
            {
                for(int j = 0; j < 7; ++j)
                {
                    d_tileClips[k].x = j * TILE_SIDE_X + offset_w;
                    d_tileClips[k].y = i * TILE_SIDE_Y*3 + offset_h;
                    d_tileClips[k].w = TILE_SIDE_X;
                    d_tileClips[k++].h = TILE_SIDE_Y*3;
                    offset_w++;
                }
            }
        }
        return success;
    }
}
