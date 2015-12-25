#include "../include/Menu.h"

namespace rpg
{
    const int Menu::OPTIONS[3] = {3, 3};
    int Menu::d_pos[3] = {(int)250*((float)config::WINDOW_H/600), (int)300*((float)config::WINDOW_H/600), (int)350*((float)config::WINDOW_H/600)};
    int Menu::d_posSP[3] = {(int)310*((float)config::WINDOW_H/600), (int)340*((float)config::WINDOW_H/600), (int)370*((float)config::WINDOW_H/600)};
    Image Menu::d_image;
    Image Menu::d_textureText[3];
    Image Menu::d_textureSP;
    Image Menu::d_textureTextSP[3];

    Menu::Menu(SDL_Renderer *renderer):d_isActive(false),d_x(100), d_y(d_pos[0]),i(0),location(0)
    {
        Menu::loadImage(renderer);
        TTF_Font *font = TTF_OpenFont("DIABLO_H.ttf", 30);
        TTF_Font *font2 = TTF_OpenFont("DIABLO_H.ttf", 22);
        SDL_Color color = {137, 128, 95, 255};
        SDL_Color color2 = {147, 149, 147, 255};
        if(font == NULL)
        {
            printf("Failed to load DIABLO_H font SDL_ttf Error: %s\n", TTF_GetError());
            exit(-1);
        }
        std::stringstream text;
        text << "Single Player";
        if(!d_textureText[0].loadText(text.str().c_str(), color, renderer, font))
        {
            printf("Unable to render Single Player text texture (menu)\n");
        }
        text.str("");
        text << "Testing";
        if(!d_textureText[1].loadText(text.str().c_str(), color, renderer, font))
        {
            printf("Unable to render Testing text texture (menu)\n");
        }
        text.str("");
        text << "Exit Diablo";
        if(!d_textureText[2].loadText(text.str().c_str(), color, renderer, font))
        {
            printf("Unable to render Exit Diablo text texture (menu)\n");
        }

        text.str("");
        text << "Single Player Characters";
        if(!d_textureSP.loadText(text.str().c_str(), color2, renderer, font2))
        {
            printf("Unable to render Single Player Characters text texture (menu)\n");
        }
        text.str("");
        text << "Warrior";
        if(!d_textureTextSP[0].loadText(text.str().c_str(), color, renderer, font2))
        {
            printf("Unable to render Warrior text texture (menu)\n");
        }
        text.str("");
        text << "Rogue";
        if(!d_textureTextSP[1].loadText(text.str().c_str(), color, renderer, font2))
        {
            printf("Unable to render Sorcerer text texture (menu)\n");
        }
        text.str("");
        text << "Sorcerer";
        if(!d_textureTextSP[2].loadText(text.str().c_str(), color, renderer, font2))
        {
            printf("Unable to render Sorcerer text texture (menu)\n");
        }

        TTF_CloseFont(font);
        TTF_CloseFont(font2);
        font = NULL;
        font2 = NULL;
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
        if(getLocation() == 0)
        {
            pentagram->render(renderer, d_x, d_pos[i]);
            pentagram->render(renderer, config::WINDOW_W - 150, d_pos[i]);
            d_textureText[0].render(renderer, (config::WINDOW_W - d_textureText[0].getWidth()) / 2, d_pos[0]);
            d_textureText[1].render(renderer, (config::WINDOW_W - d_textureText[1].getWidth()) / 2, d_pos[1]);
            d_textureText[2].render(renderer, (config::WINDOW_W - d_textureText[2].getWidth()) / 2, d_pos[2]);
        }
        else if(getLocation() == 1)
        {
            d_textureSP.render(renderer, (config::WINDOW_W - d_textureSP.getWidth()) / 2, logo->getHeight()/15 + 15);
            pentagram->render(renderer, (config::WINDOW_W - d_textureTextSP[i].getWidth()) / 2 - pentagram->getWidth() - 10, d_posSP[i]);
            pentagram->render(renderer, (config::WINDOW_W - d_textureTextSP[i].getWidth()) / 2 + d_textureTextSP[i].getWidth() + 10, d_posSP[i]);
            d_textureTextSP[0].render(renderer, (config::WINDOW_W - d_textureTextSP[0].getWidth()) / 2, d_posSP[0]);
            d_textureTextSP[1].render(renderer, (config::WINDOW_W - d_textureTextSP[1].getWidth()) / 2, d_posSP[1]);
            d_textureTextSP[2].render(renderer, (config::WINDOW_W - d_textureTextSP[2].getWidth()) / 2, d_posSP[2]);
        }
    }

    int Menu::getLocation() const
    {
        return location;
    }

    void Menu::setLocation(int l)
    {
        location = l;
    }

    void Menu::setActive()
    {
        d_isActive = !d_isActive;
    }

    bool Menu::getActive() const
    {
        return d_isActive;
    }

    void Menu::setSelection(int sel)
    {
        i = sel;
    }

    int Menu::getSelection() const
    {
        return i;
    }

    int Menu::getNbOptions(int i) const
    {
        return OPTIONS[i];
    }
}
