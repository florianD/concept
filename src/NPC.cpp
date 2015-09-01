#include "../include/NPC.h"

namespace rpg
{
    int NPC::d_size_w = 0;
    int NPC::d_size_h = 0;
    SDL_Rect NPC::d_spriteClips[64];
    Image NPC::d_spriteSheetTexture;

    enum
    {
        SOUTH=0, NORTH=2, WEST=4, EAST=6
    };

    NPC::NPC(int x, int y, int vel, int vx, int vy, std::string name, int orientation, SDL_Renderer *renderer):Character(x, y, vel, vx, vy, name, orientation)
    {
        d_box.w = 32;
        d_box.h = 32;
    }

    bool NPC::loadSpriteSheet(SDL_Renderer *renderer)
    {
        bool success = true;

        if(!d_spriteSheetTexture.load("img/object/char/npc.png", renderer))
        {
            printf("Failed to load npc texture\n");
            success = false;
        }
        else
        {
            d_size_w = (d_spriteSheetTexture.getWidth() / 8);
            d_size_h = (d_spriteSheetTexture.getHeight() / 8);

            int k = 0;
            for(int i = 0; i < 8; ++i)
            {
                for(int j = 0; j < 8; ++j)
                {
                    d_spriteClips[k].x = j * d_size_w;
                    d_spriteClips[k].y = i * d_size_h;
                    d_spriteClips[k].w = d_size_w;
                    d_spriteClips[k++].h = d_size_h;
                }
            }
        }
        return success;
    }

    void NPC::render(SDL_Renderer *renderer, SDL_Rect &cam)
    {
        /*SDL_Rect r;
        r.x = (d_box.x - d_box.y) * (config::SIDE_X / 2) / d_box.w - cam.x + 32;
        r.y = (d_box.x + d_box.y) * (config::SIDE_Y / 2) / d_box.h - cam.y;
        r.w = d_box.w;
        r.h = d_box.h;
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &r);*/

        SDL_Rect *currentClip = &d_spriteClips[(int)d_frame];
        d_spriteSheetTexture.render(renderer,
        (d_box.x - d_box.y) * (config::SIDE_X / 2) / d_box.w - cam.x,
        (d_box.x + d_box.y) * (config::SIDE_Y / 2) / d_box.h - cam.y - 64,
        currentClip);
    }

    NPC::~NPC()
    {
        d_spriteSheetTexture.free();
    }
}
