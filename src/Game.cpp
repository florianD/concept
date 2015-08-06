#include "Game.h"

namespace rpg
{
    enum
    {
        SOUTH=0, NORTH=2, WEST=4, EAST=6
    };

    Game::Game():d_running(true)
    {
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

            d_window = SDL_CreateWindow("RPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
            if(d_window == NULL)
            {
                printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                d_renderer = SDL_CreateRenderer(d_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                if(d_renderer == NULL)
                {
                    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                    success = false;
                }
                else
                {
                    SDL_SetRenderDrawColor(d_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                    int imgFlags = IMG_INIT_PNG;
                    if(!(IMG_Init(imgFlags) & imgFlags))
                    {
                        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                        success = false;
                    }
                }
            }
        }
        if(!success)
        {
            printf("Failed to initialize\n");
        }
        else
        {
            //loadBackgroundImage();

            m = new Map(d_renderer);

            characters.clear();
            player = new Player(0, 0, 1, 1, 0, 0, "Player", SOUTH, d_renderer);
            characters.push_back(player);
            characters.push_back(new NPC(32, 32, 1, 1, 0, 0, "Trainer", SOUTH, d_renderer));
            leader = player;

            camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            leader->setCamera(camera);
        }
    }

    Game::~Game()
    {
        //d_background.free();
        for(unsigned int i = 0; i < characters.size(); ++i)
        {
            delete characters[i];
        }

        delete m;
        SDL_DestroyRenderer(d_renderer);
        SDL_DestroyWindow(d_window);
        d_window = NULL;
        d_renderer = NULL;

        IMG_Quit();
        SDL_Quit();
    }

    void Game::renderAll()
    {
        leader->setCamera(camera);

        // render background
        //d_background.render(d_renderer, 0, 0, &camera);

        // render ground
        for(int i = 0; i < Map::WILD_TILES; ++i)
        {
            m->d_tileSet[i]->render(m->d_tileWild, d_renderer, camera, m->d_tileClips);
        }

        // render characters
        for(unsigned int i = 0; i < characters.size(); ++i)
        {
            characters[i]->render(d_renderer, camera.x, camera.y);
        }

        // render characters top
        for(unsigned int i = 0; i < characters.size(); ++i)
        {
            characters[i]->renderT(d_renderer, camera.x, camera.y);
        }
    }

    void Game::actions()
    {
        // characters actions
        for(unsigned int i = 0; i < characters.size(); ++i)
        {
            characters[i]->walk();
        }

        //affichage(d_renderer, camera, tileSet, player, leader, characters);
    }

    void Game::start()
    {
        Uint32 start;
        while(d_running)
        {
            start = SDL_GetTicks();
            handleEvents();

            SDL_SetRenderDrawColor(d_renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(d_renderer);

            actions();
            renderAll();

            SDL_RenderPresent(d_renderer);

            if(1000 / 30 > (SDL_GetTicks() - start))
            {
                SDL_Delay(1000 / 30 - (SDL_GetTicks() - start));
            }
        }
    }

    void Game::handleEvents()
    {
        SDL_Event e;
        // handle events on queue
        while(SDL_PollEvent(&e) != 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    d_running = false;
                    return;
            }
            player->handleEvent(e);
        }
    }

    bool Game::loadBackgroundImage()
    {
        bool success = true;

        //Load background texture
        if(!d_background.load("img/bg.png", d_renderer))
        {
            printf("Failed to load background texture\n");
            success = false;
        }
        return success;
    }
}
