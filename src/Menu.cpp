#include "../include/Menu.h"

namespace rpg
{
    SDL_Rect Menu::d_spriteClips[15];
    Image Menu::d_spriteSheetTexture;

    Menu::Menu(SDL_Renderer *renderer):d_frame(0), d_offset(0), d_clip(0){}

    bool Menu::loadSpriteSheet(SDL_Renderer *renderer)
    {
        bool success = true;

        if(!d_spriteSheetTexture.load("img/menu/menu.png", renderer))
        {
            printf("Failed to load menu texture\n");
            success = false;
        }
        else
        {
            int frames_w = 5;
            int frames_h = 3;
            int groups_w = 1;
            int groups_h = 1;

            int size_w = d_spriteSheetTexture.getWidth() / (groups_w * frames_w);
            int size_h = d_spriteSheetTexture.getHeight() / (groups_h * frames_h);

            int k = 0;
            for(int i = 0; i < groups_h * frames_h; ++i)
            {
                for(int j = 0; j < groups_w * frames_w; ++j)
                {
                    d_spriteClips[k].x = j * size_w;
                    d_spriteClips[k].y = i * size_h;
                    d_spriteClips[k].w = size_w;
                    d_spriteClips[k++].h = size_h;
                }
            }
        }
        return success;
    }

    void Menu::animate()
    {
        d_offset += 0.1;
        d_frame = d_clip % 15 + d_offset;
        if(d_offset >= 0.2)
        {
            d_offset = 0.0;
            d_clip++;
        }
    }

    void Menu::render(SDL_Renderer *renderer)
    {
        SDL_Rect *currentClip = &d_spriteClips[(int)d_frame];
        d_spriteSheetTexture.render(renderer,
        80,
        0,
        currentClip);
    }

    Menu::~Menu()
    {
        d_spriteSheetTexture.free();
    }
}
