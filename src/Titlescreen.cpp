#include "../include/Titlescreen.h"

namespace rpg
{
    Image Titlescreen::d_image;
    Logo Titlescreen::d_logo;
    Image Titlescreen::d_textureText;

    Titlescreen::Titlescreen(SDL_Renderer *renderer):d_isActive(true)
    {
        Titlescreen::loadImage(renderer);
    }

    Titlescreen::~Titlescreen(){}

    bool Titlescreen::loadImage(SDL_Renderer *renderer)
    {
        bool success = true;

        // load background image
        if(!d_image.load("img/menu/diablo.png", renderer))
        {
            printf("Failed to load diablo (titlescreen) texture\n");
            success = false;
        }
        return success;
    }

    void Titlescreen::render(SDL_Renderer *renderer, TTF_Font *font)
    {
        d_image.render(renderer, (config::WINDOW_W - d_image.getWidth()) / 2, (config::WINDOW_H - d_image.getHeight()) / 3);
        d_logo.animate();
        d_logo.render(renderer, (config::WINDOW_W - d_logo.getWidth()) / 2, (config::WINDOW_H - d_logo.getHeight() / 10));
        std::stringstream text;
        d_textureText.render(renderer, (config::WINDOW_W - d_textureText.getWidth()) / 2, (config::WINDOW_H - d_textureText.getHeight())-50);
        text.str("");
        text << "Press Enter to Continue ...";
        if(!d_textureText.loadText(text.str().c_str(), {255, 255, 255, 255}, renderer, font))
        {
            printf( "Unable to render titlescreen text texture\n" );
        }
    }

    bool Titlescreen::getActive() const
    {
        return d_isActive;
    }

    void Titlescreen::handleEvent(SDL_Event &e)
    {
        if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_RETURN:
                    d_isActive = false;
                    break;
            }
        }
    }
}
