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
            player = new Player(0, 0, 4, 0, 0, "Player", SOUTH, d_renderer);
            characters.push_back(player);
            characters.push_back(new NPC(32, 32, 4, 4, 0, "NPC", SOUTH, d_renderer));
            characters.push_back(new NPC(config::LEVEL_W - config::SIDE, 32, -4, -4, 0, "NPC", SOUTH, d_renderer));
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
            if(characters[i])
            {
                delete characters[i];
            }
        }
        characters.clear();

        delete m;
        SDL_DestroyRenderer(d_renderer);
        SDL_DestroyWindow(d_window);
        d_window = NULL;
        d_renderer = NULL;

        IMG_Quit();
        SDL_Quit();
    }

    bool Game::collision(SDL_Rect &r1, SDL_Rect &r2) const
    {
        if(r1.y >= r2.y + r2.h)
                return 0;
        if(r1.x >= r2.x + r2.w)
                return 0;
        if(r1.y + r1.h <= r2.y)
                return 0;
        if(r1.x + r1.w <= r2.x)
                return 0;
        return 1;
    }

    void Game::renderAll()
    {
        leader->setCamera(camera);

        int startX = (camera.x - (camera.x % config::SIDE)) / config::SIDE;
        int startY = (camera.y - (camera.y % config::SIDE)) /config::SIDE;
        int endX = (camera.x + camera.w + (config::SIDE - (camera.x + camera.w) % config::SIDE)) / config::SIDE;
        int endY = (camera.y + camera.h + (config::SIDE - (camera.y + camera.h) % config::SIDE)) / config::SIDE;
        if(endX > Map::MAP_WIDTH)
        {
            endX = Map::MAP_WIDTH;
        }
        if(endY > Map::MAP_HEIGHT)
        {
            endY = Map::MAP_HEIGHT;
        }

        // render background
        //d_background.render(d_renderer, 0, 0, &camera);

        // render ground
        for(int i = startY; i < endY; ++i)
        {
            for(int j = startX; j < endX; ++j)
            {
                m->d_tileSet[i][j]->render(m->d_tileWild, d_renderer, camera, m->d_tileClips);
            }
        }

        // render characters
        for(unsigned int i = 0; i < characters.size(); ++i)
        {
            characters[i]->render(d_renderer, camera);
        }

        // render characters top
        for(unsigned int i = 0; i < characters.size(); ++i)
        {
            characters[i]->renderT(d_renderer, camera);
        }
    }

    void Game::actions()
    {
        for(unsigned int i = 0; i < characters.size(); ++i)
        {
            characters[i]->walk();
        }
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

        // load background image
        if(!d_background.load("img/bg.png", d_renderer))
        {
            printf("Failed to load background texture\n");
            success = false;
        }
        return success;
    }
}
