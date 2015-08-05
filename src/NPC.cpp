#include "../include/NPC.h"

namespace rpg
{
    enum
    {
        SOUTH=0, NORTH=2, WEST=4, EAST=6
    };

    NPC::NPC(int x, int y, int vel, int vx, int vy, int id, string name, int orientation, SDL_Renderer *renderer):Character(x, y, vel, vx, vy, id, name, orientation)
    {
        loadSpriteSheet(renderer);
    }

    bool NPC::loadSpriteSheet(SDL_Renderer *renderer)
    {
        bool success = true;

        if(!d_spriteSheetTexture.load("img/object/char/trainer1.png", renderer))
        {
            printf("Failed to load walking animation texture\n");
            success = false;
        }
        else
        {
            int k = 0;
            for(int i = 0; i <= 2; i+=2)
            {
                for(int j = 0; j < 12; ++j)
                {
                    d_spriteClips[k].x = j * config::SIDE;
                    d_spriteClips[k].y = (i+1) * config::SIDE;
                    d_spriteClips[k].w = config::SIDE;
                    d_spriteClips[k++].h = config::SIDE;

                    d_spriteClips[k].x = j * config::SIDE;
                    d_spriteClips[k].y = i * config::SIDE;
                    d_spriteClips[k].w = config::SIDE;
                    d_spriteClips[k++].h = config::SIDE;
                }
            }
        }
        return success;
    }

    NPC::~NPC()
    {
        d_spriteSheetTexture.free();
    }
}
