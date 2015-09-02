#include <algorithm>
#include "Game.h"

namespace rpg
{
    enum
    {
        SOUTH=0, NORTH=1, WEST=2, EAST=3, DSOUTH=4, DNORTH=5, DWEST=6, DEAST=7
    };

    bool compare(const Character *c1, const Character *c2)
    {
        return c1->getY() < c2->getY() || (!(c2->getY() < c1->getY()) && c1->getX() < c2->getX());
    }

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

            Player::loadSpriteSheet(d_renderer);
            NPC::loadSpriteSheet(d_renderer);

            player = new Player(0, 0, 2, 0, 0, "Player", SOUTH, d_renderer);
            characters.push_back(player);
            characters.push_back(new NPC(32, 96, 0, 0, 0, "NPC", SOUTH, d_renderer));
            characters.push_back(new NPC(64, 96, 0, 0, 0, "NPC", NORTH, d_renderer));
            characters.push_back(new NPC(96, 96, 0, 0, 0, "NPC", EAST, d_renderer));
            characters.push_back(new NPC(128, 96, 0, 0, 0, "NPC", WEST, d_renderer));
            characters.push_back(new NPC(32, 128, 0, 0, 0, "NPC", DSOUTH, d_renderer));
            characters.push_back(new NPC(64, 128, 0, 0, 0, "NPC", DNORTH, d_renderer));
            characters.push_back(new NPC(96, 128, 0, 0, 0, "NPC", DEAST, d_renderer));
            characters.push_back(new NPC(128, 128, 0, 0, 0, "NPC", DWEST, d_renderer));
            characters.push_back(new NPC(32, 32, 2, 2, 0, "NPC", SOUTH, d_renderer));
            characters.push_back(new NPC(config::LEVEL_W / (config::SIDE_X / player->getRect().w) - config::SIDE_X / 2, 64, -2, -2, 0, "NPC", SOUTH, d_renderer));

            std::sort(characters.begin(), characters.end(), compare);

            leader = player;

            camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            setCamera(leader->getRect());
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

    void Game::setCamera(SDL_Rect box)
    {
        if(config::LEVEL_W >= config::WINDOW_W)
        {
            camera.x = ((box.x - box.y) * (config::SIDE_X / 2) / box.w + config::SIDE_X / 2) - config::WINDOW_W / 2;
        }
        if(config::LEVEL_H >= config::WINDOW_H)
        {
            camera.y = ((box.x + box.y) * (config::SIDE_Y / 2) / box.h + config::SIDE_Y / 2) - config::WINDOW_H / 2;
        }
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
        setCamera(leader->getRect());

        int startX = (int)(leader->getX() / leader->getRect().w - round((SCREEN_WIDTH / 2) / (config::SIDE_X / 4)));
        int endX = (int)(leader->getX() / leader->getRect().w + round((SCREEN_WIDTH / 2) / (config::SIDE_X / 4)));
        int startY = (int)(leader->getY() / leader->getRect().h - round((SCREEN_HEIGHT / 2) / (config::SIDE_Y / 2)));
        int endY = (int)(leader->getY() / leader->getRect().h + round((SCREEN_HEIGHT / 2) / (config::SIDE_Y / 2)));
        startX = startX >= 0 ? startX : 0;
        endX = endX <= Map::MAP_WIDTH - 1 ? endX : Map::MAP_WIDTH - 1;
        startY = startY >= 0 ? startY : 0;
        endY = endY <= Map::MAP_HEIGHT - 1 ? endY : Map::MAP_HEIGHT - 1;

        // render background
        //d_background.render(d_renderer, 0, 0, &camera);

        // render ground (isometric view)
        for(int i = startY; i <= endY; ++i)
        {
            for(int j = endX; j >= startX; --j)
            {
                m->d_tileSet[i][j]->render(m->d_tileWild, d_renderer, camera, m->d_tileClips);
            }
        }

        // render characters
        for(unsigned int i = 0; i < characters.size(); ++i)
        {
            characters[i]->render(d_renderer, camera);
        }
    }

    void Game::actions()
    {
        for(unsigned int i = 0; i < characters.size(); ++i)
        {
            characters[i]->walk();
        }
        std::sort(characters.begin(), characters.end(), compare);
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
