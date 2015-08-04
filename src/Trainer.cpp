#include "../include/Trainer.h"

namespace rpg
{
    enum
    {
        SOUTH=0, NORTH=2, WEST=4, EAST=6
    };

    Trainer::Trainer(int x, int y, int vel, int vx, int vy, int id, string name, int orientation, SDL_Renderer *renderer):Character(x, y, vel, vx, vy, id, name, orientation)
    {
        loadSpriteSheet(renderer);
    }

    bool Trainer::loadSpriteSheet(SDL_Renderer *renderer)
    {
        bool success = true;

        if(!d_spriteSheetTexture.load(config::d_dir+"/object/char/trainer1.png", renderer))
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
                    d_spriteClips[k].x = j * config::d_side;
                    d_spriteClips[k].y = (i+1) * config::d_side;
                    d_spriteClips[k].w = config::d_side;
                    d_spriteClips[k++].h = config::d_side;

                    d_spriteClips[k].x = j * config::d_side;
                    d_spriteClips[k].y = i * config::d_side;
                    d_spriteClips[k].w = config::d_side;
                    d_spriteClips[k++].h = config::d_side;
                }
            }
        }
        return success;
    }

    Trainer::~Trainer()
    {
        d_spriteSheetTexture.free();
    }

    /*void Trainer::render(SDL_Renderer *renderer, int camx, int camy)
    {
        SDL_Rect *currentClip = &d_spriteClips[d_frame];
        //d_spriteSheetTexture.render(renderer, d_x - camx, d_y - camy, currentClip);
        d_spriteSheetTexture.render(renderer, d_x, d_y, currentClip);
    }

    void Trainer::renderT(SDL_Renderer *renderer, int camx, int camy)
    {
        SDL_Rect *currentClip = &d_spriteClips[d_frame+1];
        //d_spriteSheetTexture.render(renderer, d_x - camx, d_y - camy - config::d_side, currentClip);
        d_spriteSheetTexture.render(renderer, d_x, d_y - config::d_side, currentClip);
    }*/
}
