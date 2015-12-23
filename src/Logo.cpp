#include "../include/Logo.h"

namespace rpg
{
    SDL_Rect Logo::d_spriteClips[15];
    Image Logo::d_spriteSheetTexture;

    Logo::Logo():d_frame(0), d_offset(0), d_clip(0){}

    bool Logo::loadSpriteSheet(SDL_Renderer *renderer, std::string path)
    {
        bool success = true;

        if(!d_spriteSheetTexture.load(path, renderer))
        {
            printf("Failed to load menu texture\n");
            success = false;
        }
        else
        {
            int frames_w = 1;
            int frames_h = 15;
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

    void Logo::animate()
    {
        d_offset += 0.1;
        d_frame = (d_clip % 15) + d_offset;
        if(d_offset >= 0.2)
        {
            d_offset = 0.0;
            d_clip++;
        }
    }

    int Logo::getHeight() const
    {
        return d_spriteSheetTexture.getHeight();
    }

    int Logo::getWidth() const
    {
        return d_spriteSheetTexture.getWidth();
    }

    void Logo::render(SDL_Renderer *renderer, int x, int y)
    {
        SDL_Rect *currentClip = &d_spriteClips[(int)d_frame];
        d_spriteSheetTexture.render(renderer,
        x,
        y,
        currentClip);
    }

    Logo::~Logo()
    {
        d_spriteSheetTexture.free();
    }
}
