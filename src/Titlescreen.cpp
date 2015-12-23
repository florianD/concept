#include "../include/Titlescreen.h"

namespace rpg
{
    Image Titlescreen::d_image;
    Image Titlescreen::d_textureText;

    Titlescreen::Titlescreen(SDL_Renderer *renderer, TTF_Font *font):d_isActive(true)
    {
        Titlescreen::loadImage(renderer);
        std::stringstream text;
        text << "Press Enter to Continue ...";
        if(!d_textureText.loadText(text.str().c_str(), {255, 255, 255, 255}, renderer, font))
        {
            printf( "Unable to render titlescreen text texture\n" );
        }
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

    void Titlescreen::render(SDL_Renderer *renderer, Logo *logo)
    {
        d_image.render(renderer, (config::WINDOW_W - d_image.getWidth()) / 2, (config::WINDOW_H - d_image.getHeight()) / 3);
        logo->animate();
        logo->render(renderer, (config::WINDOW_W - logo->getWidth()) / 2, (config::WINDOW_H - logo->getHeight() / 10));
        d_textureText.render(renderer, (config::WINDOW_W - d_textureText.getWidth()) / 2, (config::WINDOW_H - d_textureText.getHeight())-50);
    }

    bool Titlescreen::getActive() const
    {
        return d_isActive;
    }

    void Titlescreen::setActive()
    {
        d_isActive = !d_isActive;
    }
}
