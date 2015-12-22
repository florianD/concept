#include "../include/Pentagram.h"

namespace rpg
{
    SDL_Rect Pentagram::d_spriteClips[9];
    Image Pentagram::d_spriteSheetTexture;

    Pentagram::Pentagram():d_frame(0), d_offset(0), d_clip(0){}

    bool Pentagram::loadSpriteSheet(SDL_Renderer *renderer)
    {
        bool success = true;

        if(!d_spriteSheetTexture.load("img/menu/pentagram.png", renderer))
        {
            printf("Failed to load pentagram texture\n");
            success = false;
        }
        else
        {
            int frames_w = 9;
            int frames_h = 1;
            int groups_w = 1;
            int groups_h = 1;

            int size_w = d_spriteSheetTexture.getWidth() / (groups_w * frames_w);
            int size_h = d_spriteSheetTexture.getHeight() / (groups_h * frames_h);

            int offset_w = 0;

            int k = 0;
            for(int i = 0; i < groups_h * frames_h; ++i)
            {
                for(int j = 0; j < groups_w * frames_w; ++j)
                {
                    d_spriteClips[k].x = j * size_w + offset_w;
                    d_spriteClips[k].y = i * size_h;
                    d_spriteClips[k].w = size_w;
                    d_spriteClips[k++].h = size_h;
                    offset_w++;
                }
            }
        }
        return success;
    }

    void Pentagram::animate()
    {
        d_offset += 0.1;
        d_frame = (d_clip % 9) + d_offset;
        if(d_offset >= 0.2)
        {
            d_offset = 0.0;
            d_clip++;
        }
    }

    void Pentagram::render(SDL_Renderer *renderer, int x, int y)
    {
        SDL_Rect *currentClip = &d_spriteClips[(int)d_frame];
        d_spriteSheetTexture.render(renderer,
        x,
        y,
        currentClip);
    }

    Pentagram::~Pentagram()
    {
        d_spriteSheetTexture.free();
    }
}
