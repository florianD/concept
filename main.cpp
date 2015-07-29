#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_thread.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "include/config.h"
#include "include/Image.h"
#include "include/Tile.h"
#include "include/Object.h"
#include "include/Player.h"
#include "include/Trainer.h"
using namespace std;
using namespace rpg;

//The dimensions of the level
const int LEVEL_WIDTH = config::d_wrapper_w;
const int LEVEL_HEIGHT = config::d_wrapper_h;

//Screen dimension constants
const int SCREEN_WIDTH = config::d_win_w;
const int SCREEN_HEIGHT = config::d_win_h;

//Tile constants
const int TILE_WIDTH = config::d_side;
const int TILE_HEIGHT = config::d_side;

const int WILD_TILES = config::d_c * config::d_l;
const int WILD_TILE_SPRITES = 12;

//Scene textures
Image background;
Image tileTexture;
vector<SDL_Rect> tileClips(WILD_TILE_SPRITES);

bool setTiles(Tile* tiles[])
{
	//Success flag
	bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map("world.map");

    //If the map couldn't be loaded
    if(map == NULL)
    {
		printf("Unable to load map file\n");
		tilesLoaded = false;
    }
	else
	{
		//Initialize the tiles
		for(int i = 0; i < WILD_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if(map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if((tileType >= 0) && (tileType < WILD_TILE_SPRITES))
			{
				tiles[i] = new Tile(x, y, tileType);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if(x >= LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}

		//Clip the sprite sheet
		if(tilesLoaded)
		{
            int k = 0;
            for(int i = 0; i < 3; ++i)
            {
                for(int j = 0; j < 4; ++j)
                {
                    tileClips[k].x = j * config::d_side;
                    tileClips[k].y = i * config::d_side;
                    tileClips[k].w = TILE_WIDTH;
                    tileClips[k++].h = TILE_HEIGHT;
                }
            }
		}
	}

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

bool loadMedia(SDL_Renderer *gRenderer, Tile *tiles[])
{
	bool success = true;

	//Load background texture
	if(!background.load("bg.png", gRenderer))
	{
		printf("Failed to load background texture\n");
		success = false;
	}
	if(!tileTexture.load(config::d_dir+"/wild.png", gRenderer))
    {
        printf("Failed to load wild.png\n");
        success = false;
    }
    if(!setTiles(tiles))
    {
		printf("Failed to load tile set\n");
		success = false;
    }
	return success;
}

void close(SDL_Window *gWindow, SDL_Renderer *gRenderer, Tile *tiles[], vector<Object*> characters)
{
    for(unsigned int i = 0; i < WILD_TILES; ++i)
    {
        if(tiles[i] == NULL)
        {
            delete tiles[i];
            tiles[i] = NULL;
        }
    }

    for(unsigned int i = 0; i < characters.size(); ++i)
    {
        delete characters[i];
    }

    tileTexture.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

/*int threadFunction(void *data)
{
    Object* character = (Object*)data;

    while(continuer)
    {
        character->walk();

    }

    return 0;
}*/

void affichage(SDL_Renderer *gRenderer, SDL_Rect &camera, Tile **tileSet, Player &player, Object *leader, vector<Object*> characters)
{
    leader->setCamera(camera);

    //Render background
    //background.render(gRenderer, 0, 0, &camera);

    // render ground
    for(unsigned int i = 0; i < WILD_TILES; ++i)
    {
        tileSet[i]->render(tileTexture, gRenderer, camera, tileClips);
    }

    // render characters
    player.render(gRenderer, camera.x, camera.y);
    for(unsigned int i = 0; i < characters.size(); ++i)
    {
        characters[i]->render(gRenderer, camera.x, camera.y);
    }

    // render characters top
    player.renderT(gRenderer, camera.x, camera.y);
    for(unsigned int i = 0; i < characters.size(); ++i)
    {
        characters[i]->renderT(gRenderer, camera.x, camera.y);
    }

    // update screen
    SDL_RenderPresent(gRenderer);

    //SDL_Delay(50); // 130
}

void game(SDL_Renderer *gRenderer, SDL_Rect &camera, Tile **tileSet, Player &player, Object *leader, vector<Object*> characters)
{
    // characters actions
    player.walk();
    for(unsigned int i = 0; i < characters.size(); ++i)
    {
        characters[i]->walk();
    }

    affichage(gRenderer, camera, tileSet, player, leader, characters);

    SDL_RenderClear(gRenderer);

    player.walk2();
    for(unsigned int i = 0; i < characters.size(); ++i)
    {
        characters[i]->walk2();
    }

    affichage(gRenderer, camera, tileSet, player, leader, characters);
}

int main(int argc, char* args[])
{
    SDL_Window *gWindow = NULL;
    SDL_Renderer *gRenderer = NULL;
    // Variables propres à l'application
    vector<Object*> characters;
    Object *leader = NULL;
    enum
    {
        SOUTH=0, NORTH=2, WEST=4, EAST=6
    };

	bool success = true;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled");
		}

		gWindow = SDL_CreateWindow("Concept", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
		if( gWindow == NULL )
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	if(!success)
	{
		printf( "Failed to initialize\n" );
	}
	else
	{
	    Tile *tileSet[WILD_TILES];
		if(!loadMedia(gRenderer, tileSet))
		{
			printf( "Failed to load media\n" );
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			Player player(0, 0, config::d_side/2, 0, 0, 0, "Player", SOUTH, gRenderer);
			Trainer trainer(config::d_side, config::d_side, config::d_side/2, config::d_side/2, 0, 0, "Trainer", SOUTH, gRenderer);
			leader = &player;
			characters.push_back(&trainer);

			// the camera area
			SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            leader->setCamera(camera);

            // lancement d'un thread
            //SDL_Thread* threadID = SDL_CreateThread(threadFunction, "Thread", (Object*)&player);

			// while application is running
			while(!quit)
			{
				// handle events on queue
				while(SDL_PollEvent(&e) != 0)
				{
					// user requests quit
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
					// handle input
					player.handleEvent(e);
				}
				// clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderClear(gRenderer);

                game(gRenderer, camera, tileSet, player, leader, characters);

                if(trainer.getX() == (config::d_c - 1) * config::d_side)
                {
                    trainer.setVelX(-trainer.getVel());
                }
                if(trainer.getX() == 0)
                {
                    trainer.setVelX(trainer.getVel());
                }
			}
			//continuer = 0;
            //SDL_WaitThread(threadID, NULL);
		}
        close(gWindow, gRenderer, tileSet, characters);
	}
	return 0;
}
