#include <algorithm>
#include "Game.h"

namespace rpg
{
    int Game::nextLeader = 0;
    Image Game::d_textureFPS;

    enum {DSOUTH, SOUTH, DWEST, WEST, DNORTH, NORTH, DEAST, EAST};

    bool compare(const Character *c1, const Character *c2)
    {
        return c1->getY() < c2->getY() || (!(c2->getY() < c1->getY()) && c1->getX() < c2->getX());
    }

    Game::Game():d_running(true), d_fullscreen(false), d_inGame(false), m(NULL)
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

                    if(TTF_Init() == -1)
                    {
                        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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
            SDL_SetWindowFullscreen(d_window, d_fullscreen ? SDL_WINDOW_FULLSCREEN : 0);

            d_font = TTF_OpenFont("Tahoma.ttf", 12);
            if(d_font == NULL)
            {
                printf( "Failed to load Tahoma font! SDL_ttf Error: %s\n", TTF_GetError() );
                exit(-1);
            }

            camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

            Logo::loadSpriteSheet(d_renderer, "img/menu/logo.png");
            Pentagram::loadSpriteSheet(d_renderer, "img/menu/pentagram.png");
            logo = new Logo;

            titlescreen = new Titlescreen(d_renderer, d_font);

            pentagram = new Pentagram;
            menu = new Menu(d_renderer);

            //std::cout << SDL_GetWindowBrightness(d_window) << " ";
            SDL_SetWindowBrightness(d_window, 1);
        }
    }

    void Game::clearChars()
    {
        for(unsigned int i = 0; i < characters.size(); ++i)
        {
            if(characters[i])
            {
                delete characters[i];
            }
        }
        characters.clear();
    }

    Game::~Game()
    {
        //d_background.free();

        d_textureFPS.free();
        TTF_CloseFont(d_font);
        d_font = NULL;

        clearChars();

        if(m)
            delete m;
        delete logo;
        delete pentagram;
        delete titlescreen;
        delete menu;
        SDL_DestroyRenderer(d_renderer);
        SDL_DestroyWindow(d_window);
        d_window = NULL;
        d_renderer = NULL;

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void Game::initChars(Player *player)
    {
        clearChars();
        NPC::loadSpriteSheet(d_renderer);

        characters.push_back(player);
        /*characters.push_back(new NPC(32, 96, 0, 0, 0, "NPC", SOUTH, d_renderer));
        characters.push_back(new NPC(64, 96, 0, 0, 0, "NPC", NORTH, d_renderer));
        characters.push_back(new NPC(96, 96, 0, 0, 0, "NPC", EAST, d_renderer));
        characters.push_back(new NPC(128, 96, 0, 0, 0, "NPC", WEST, d_renderer));
        characters.push_back(new NPC(32, 128, 0, 0, 0, "NPC", DSOUTH, d_renderer));
        characters.push_back(new NPC(64, 128, 0, 0, 0, "NPC", DNORTH, d_renderer));
        characters.push_back(new NPC(96, 128, 0, 0, 0, "NPC", DEAST, d_renderer));
        characters.push_back(new NPC(128, 128, 0, 0, 0, "NPC", DWEST, d_renderer));*/
        characters.push_back(new NPC(0, 32, 2, 2, 0, "NPC", EAST, d_renderer));
        characters.push_back(new NPC(config::LEVEL_W / (config::SIDE_X / player->getRect().w) - config::SIDE_X / 8, 64, -2, -2, 0, "NPC", SOUTH, d_renderer));
        characters.push_back(new NPC(160, 0, 2, 0, 2, "NPC", SOUTH, d_renderer));
        characters.push_back(new NPC(192, config::LEVEL_H / (config::SIDE_Y / player->getRect().h) - config::SIDE_Y / 4, 2, 0, -2, "NPC", WEST, d_renderer));

        std::sort(characters.begin(), characters.end(), compare);

        leader = player;
        nextLeader = 0;
        setCamera(leader->getRect());
    }

    Character *Game::getId(int id) const
    {
        for(unsigned int i = 0; i < characters.size(); ++i)
        {
            if(characters[i]->getId() == id)
            {
                return characters[i];
            }
        }
    }

    void Game::setCamera(SDL_Rect box)
    {
        if(config::LEVEL_W >= config::WINDOW_W)
        {
            camera.x = ((box.x - box.y) * (config::SIDE_X / 2) / box.w + config::SIDE_X / 2) - config::WINDOW_W / 2;
        }
        if(config::LEVEL_H >= config::WINDOW_H)
        {
            camera.y = ((box.x + box.y) * (config::SIDE_Y / 2) / box.h + config::SIDE_Y / 2) - config::WINDOW_H / 2 + 128; // +0
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

	/*bool Collision(AABB box1,AABB box2)
	{
	   if((box2.x >= box1.x + box1.w)      // trop à droite
		|| (box2.x + box2.w <= box1.x) // trop à gauche
		|| (box2.y >= box1.y + box1.h) // trop en bas
		|| (box2.y + box2.h <= box1.y))  // trop en haut
			  return false;
	   else
			  return true;
	}*/

    void Game::renderAll()
    {
        int startX, endX, startY, endY;
        setCamera(leader->getRect());

        startX = (int)(leader->getX() / leader->getRect().w - round((SCREEN_WIDTH / 2) / (config::SIDE_X / 4)));
        endX = (int)(leader->getX() / leader->getRect().w + round((SCREEN_WIDTH / 2) / (config::SIDE_X / 4)));
        startY = (int)(leader->getY() / leader->getRect().h - round((SCREEN_HEIGHT / 2) / (config::SIDE_Y / 2)));
        endY = (int)(leader->getY() / leader->getRect().h + round((SCREEN_HEIGHT / 2) / (config::SIDE_Y / 2)));
        startX = startX >= 0 ? startX : 0;
        endX = endX <= Map::MAP_WIDTH - 1 ? endX : Map::MAP_WIDTH - 1;
        startY = startY >= 0 ? startY : 0;
        endY = endY <= Map::MAP_HEIGHT - 1 ? endY : Map::MAP_HEIGHT - 1;

        // render background
        //d_background.render(d_renderer, 0, 0, &camera);

        // render ground (isometric view)
        for(int i = startY; i <= endY; ++i)
        {
            for(int j = startX; j <= endX; ++j)
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
        std::stringstream fpsText;
        Uint32 start;

        Timer update;
        update.start();
        Timer fps;
        fps.start();

        int frames = 0;
        int curFps = 0;
        float avgFps = 0;
        while(d_running)
        {
            start = SDL_GetTicks();
            handleEvents();

            SDL_SetRenderDrawColor(d_renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(d_renderer);

            if(d_inGame)
            {
                if(!menu->getActive())
                {
                    actions();
                    renderAll();
                    //Font::render(d_renderer, "Single Player", 50, 50);
                }
                else
                {
                    renderAll();
                    menu->render(d_renderer, logo, pentagram);
                }
            }
            else if(titlescreen->getActive())
            {
                titlescreen->render(d_renderer, logo);
            }
            else
            {
                menu->render(d_renderer, logo, pentagram);
            }

            if(1000 / 30 > (SDL_GetTicks() - start))
            {
                SDL_Delay(1000 / 30 - (SDL_GetTicks() - start));
            }

            d_textureFPS.render(d_renderer, SCREEN_WIDTH - 110, 2);
            if(update.getTicks() > 1000)
            {
                //std::cout << "SDL_GetTicks() : " << SDL_GetTicks() << " - start : " << start << std::endl << " = " << SDL_GetTicks()-start << std::endl;
                curFps = 1000 / (SDL_GetTicks() - start); // real time
                avgFps = frames / (fps.getTicks() / 1000.f); // average

                fpsText.str("");
                fpsText << "FPS : " << curFps << " (" << avgFps << ")";

                if(!d_textureFPS.loadText(fpsText.str().c_str(), {255, 255, 255, 255}, d_renderer, d_font))
                {
                    printf( "Unable to render FPS texture\n" );
                }

                update.start();
            }
            SDL_RenderPresent(d_renderer);
            frames++;
        }
    }

    void Game::handleEvents()
    {
        SDL_Event e;
        // handle events on queue
        while(SDL_PollEvent(&e) != 0)
        {
            if(d_inGame)
            {
                player->handleEvent(e);
            }
            switch(e.type)
            {
                case SDL_QUIT:
                    d_running = false;
                    return;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_PAGEUP:
                            nextLeader = (nextLeader + 1) % characters.size();
                            leader = getId(nextLeader);
                            return;
                        case SDLK_PAGEDOWN:
                            nextLeader = (nextLeader == 0) ? characters.size()-1 : (nextLeader - 1) % characters.size();
                            leader = getId(nextLeader);
                            return;
                        case SDLK_RETURN:
                            if(d_inGame)
                            {
                                if(!menu->getActive())
                                {
                                    nextLeader = player->getId();
                                    leader = getId(nextLeader);
                                }
                                else
                                {
                                    if(menu->getSelection() == 0)
                                    {
                                        menu->setActive();
                                    }
                                    else if(menu->getSelection() == 3)
                                    {
                                        // restart in town
                                        player->moveTo(0, 0);
                                    }
                                    else if(menu->getSelection() == 4)
                                    {
                                        clearChars();
                                        delete m;
                                        m = NULL;
                                        d_inGame = false;
                                        menu->setSelection(0);
                                        menu->setLocation(0);
                                    }
                                    else if(menu->getSelection() == 5)
                                    {
                                        d_running = false;
                                    }
                                }
                            }
                            else if(titlescreen->getActive())
                            {
                                titlescreen->setActive();
                                Logo::loadSpriteSheet(d_renderer, "img/menu/smlogo.png");
                                menu->setActive();
                                menu->setSelection(0);
                            }
                            else if(menu->getActive())
                            {
                                if(menu->getLocation() == 0) // main
                                {
                                    if(menu->getSelection() == 0)
                                    {
                                        Pentagram::loadSpriteSheet(d_renderer, "img/menu/pentagram2.png");
                                        menu->setLocation(1);
                                    }
                                    else if(menu->getSelection() == 1)
                                    {
                                        menu->setActive();
                                        d_inGame = true;
                                        Warrior::loadSpriteSheet(d_renderer);
                                        player = new Warrior(0, 0, 2, 0, 0, "Player", SOUTH);
                                        initChars(player);
                                        m = new Map(d_renderer);
                                    }
                                    else if(menu->getSelection() == 2)
                                    {
                                        menu->setActive();
                                        d_inGame = false;
                                        d_running = false;
                                    }
                                }
                                else if(menu->getLocation() == 1) // characters
                                {
                                    if(menu->getSelection() == 0)
                                    {
                                        // Warrior
                                        Warrior::loadSpriteSheet(d_renderer);
                                        player = new Warrior(0, 0, 2, 0, 0, "Player", SOUTH);
                                        menu->setActive();
                                        d_inGame = true;
                                        initChars(player);
                                        m = new Map(d_renderer);
                                    }
                                    else if(menu->getSelection() == 1)
                                    {
                                        // Rogue
                                        // todo
                                        menu->setActive();
                                        d_inGame = true;
                                        initChars(player);
                                        m = new Map(d_renderer);
                                    }
                                    else if(menu->getSelection() == 2)
                                    {
                                        // Sorcerer
                                        Sorcerer::loadSpriteSheet(d_renderer);
                                        player = new Sorcerer(0, 0, 2, 0, 0, "Player", SOUTH);
                                        menu->setActive();
                                        d_inGame = true;
                                        initChars(player);
                                        m = new Map(d_renderer);
                                    }
                                }
                            }
                            return;
                        case SDLK_BACKSPACE:
                            //initChars();
                            return;
                        case SDLK_KP_0:
                            for(unsigned int i = 0; i < characters.size(); ++i)
                            {
                                characters[i]->setVelX(0);
                                characters[i]->setVelY(0);
                            }
                            return;
                        case SDLK_KP_1:
                            d_fullscreen = !d_fullscreen;
                            SDL_SetWindowFullscreen(d_window, d_fullscreen ? SDL_WINDOW_FULLSCREEN : 0);

                            /*SDL_DisplayMode target;
                            target = {1600, 900, 0, 0, 0};
                            SDL_SetWindowDisplayMode(d_window, &target);*/
                            return;
                        case SDLK_UP:
                            if(menu->getActive())
                            {
                                menu->setSelection((menu->getSelection() == 0) ? menu->getNbOptions(menu->getLocation()) - 1 : (menu->getSelection() - 1) % menu->getNbOptions(menu->getLocation()));
                            }
                            return;
                        case SDLK_DOWN:
                            if(menu->getActive())
                            {
                                menu->setSelection((menu->getSelection() + 1) % menu->getNbOptions(menu->getLocation()));
                            }
                            return;
                        case SDLK_ESCAPE:
                            if(d_inGame)
                            {
                                //d_inGame = false;
                                if(menu->getActive())
                                {
                                    menu->setActive();
                                }
                                else
                                {
                                    menu->setActive();
                                    menu->setLocation(2);
                                    menu->setSelection(0);
                                }
                            }
                            else if(titlescreen->getActive())
                            {
                                d_running = false;
                            }
                            else if(menu->getActive())
                            {
                                if(menu->getLocation() == 0)
                                {
                                    Logo::loadSpriteSheet(d_renderer, "img/menu/logo.png");
                                    menu->setActive();
                                    titlescreen->setActive();
                                }
                                else if(menu->getLocation() == 1)
                                {
                                    Pentagram::loadSpriteSheet(d_renderer, "img/menu/pentagram.png");
                                    menu->setSelection(0);
                                    menu->setLocation(0);
                                }
                            }
                            return;
                    }
            }
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
