#include "../include/Menu.h"

namespace rpg
{
    int Menu::d_pos[3] = {270, 320, 370};
    Image Menu::d_image;
    Image Menu::d_textureText[3];

    Menu::Menu(SDL_Renderer *renderer):d_isActive(false),d_x(50), d_y(d_pos[0]),i(0)
    {
        Menu::loadImage(renderer);
        TTF_Font *font = TTF_OpenFont("DIABLO_H.ttf", 30);
        SDL_Color color = {137, 128, 95, 255};
        if(font == NULL)
        {
            printf( "Failed to load DIABLO_H font SDL_ttf Error: %s\n", TTF_GetError() );
            exit(-1);
        }
        std::stringstream text;
        text << "Single Player";
        if(!d_textureText[0].loadText(text.str().c_str(), color, renderer, font))
        {
            printf( "Unable to render Single Player text texture\n" );
        }
        text.str("");
        text << "Testing";
        if(!d_textureText[1].loadText(text.str().c_str(), color, renderer, font))
        {
            printf( "Unable to render Testing text texture\n" );
        }
        text.str("");
        text << "Exit Diablo";
        if(!d_textureText[2].loadText(text.str().c_str(), color, renderer, font))
        {
            printf( "Unable to render Exit Diablo text texture\n" );
        }
        TTF_CloseFont(font);
        font = NULL;
    }

    Menu::~Menu(){}

    bool Menu::loadImage(SDL_Renderer *renderer)
    {
        bool success = true;

        // load background image
        if(!d_image.load("img/menu/evil.png", renderer))
        {
            printf("Failed to load evil (menu) texture\n");
            success = false;
        }
        return success;
    }

    void Menu::render(SDL_Renderer *renderer, Logo *logo, Pentagram *pentagram)
    {
        d_image.render(renderer, (config::WINDOW_W - d_image.getWidth()) / 2, (config::WINDOW_H - d_image.getHeight()) / 2);
        logo->animate();
        logo->render(renderer, (config::WINDOW_W - logo->getWidth()) / 2, 0);
        pentagram->animate();
        pentagram->render(renderer, d_x, d_y);
        pentagram->render(renderer, config::WINDOW_W - 100, d_y);
        d_textureText[0].render(renderer, (config::WINDOW_W - d_textureText[0].getWidth()) / 2, logo->getHeight()/15+60);
        d_textureText[1].render(renderer, (config::WINDOW_W - d_textureText[1].getWidth()) / 2, logo->getHeight()/15+110);
        d_textureText[2].render(renderer, (config::WINDOW_W - d_textureText[2].getWidth()) / 2, logo->getHeight()/15+160);
    }

    void Menu::setActive()
    {
        d_isActive = true;
    }

    bool Menu::getActive() const
    {
        return d_isActive;
    }

    int Menu::getSelection() const
    {
        return i;
    }

    void Menu::handleEvent(SDL_Event &e)
    {
        if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_RETURN:
                    if(i == 1)
                        d_isActive = false;
                    return;
                case SDLK_UP:
                    i = (i == 0) ? 3-1 : (i - 1) % 3;
                    d_y = d_pos[i];
                    return;
                case SDLK_DOWN:
                    i = (i + 1) % 3;
                    d_y = d_pos[i];
                    return;
            }
        }
    }
}
